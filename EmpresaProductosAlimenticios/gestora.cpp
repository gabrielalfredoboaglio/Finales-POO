#include "gestora.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    // Liberar memoria de productos
    for(Producto* p : productos) {
        delete p;
    }

    // Liberar memoria de ingredientes
    for(Ingrediente* ing : ingredientes) {
        delete ing;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Producto* Gestora::buscarProducto(int codigo) {
    for(Producto* p : productos) {
        if(p->getCodigo() == codigo) {
            return p;
        }
    }
    return nullptr;
}

Ingrediente* Gestora::buscarIngrediente(int codigo) {
    for(Ingrediente* ing : ingredientes) {
        if(ing->getCodigo() == codigo) {
            return ing;
        }
    }
    return nullptr;
}

void Gestora::agregarProducto(Producto* producto) {
    productos.push_back(producto);
}

void Gestora::agregarIngrediente(Ingrediente* ingrediente) {
    ingredientes.push_back(ingrediente);
}

vector<Producto*> Gestora::getProductos() {
    return productos;
}

vector<Ingrediente*> Gestora::getIngredientes() {
    return ingredientes;
}

// ========== PUNTO 1: GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(char* archProductos,
                              char* archIngredientes,
                              char* archProductosIngredientes,
                              char* archProductosCompuestos) {

    // ========== ARCHIVO 1: PRODUCTOS ==========
    ofstream archiP(archProductos, ios::binary);

    if(!archiP.is_open()) {
        cout << "Error al crear " << archProductos << endl;
        return;
    }

    ProductoArchivo paux;

    for(Producto* prod : productos) {
        paux.codigo = prod->getCodigo();
        strcpy(paux.nombre, prod->getNombre());
        paux.tipo = prod->getTipo();

        archiP.write((char*)&paux, sizeof(ProductoArchivo));
    }

    archiP.close();

    // ========== ARCHIVO 2: INGREDIENTES ==========
    ofstream archiI(archIngredientes, ios::binary);

    if(!archiI.is_open()) {
        cout << "Error al crear " << archIngredientes << endl;
        return;
    }

    IngredienteArchivo iaux;

    for(Ingrediente* ing : ingredientes) {
        iaux.codigo = ing->getCodigo();
        strcpy(iaux.nombre, ing->getNombre());

        archiI.write((char*)&iaux, sizeof(IngredienteArchivo));
    }

    archiI.close();

    // ========== ARCHIVO 3: PRODUCTOS_INGREDIENTES ==========
    ofstream archiPI(archProductosIngredientes, ios::binary);

    if(!archiPI.is_open()) {
        cout << "Error al crear " << archProductosIngredientes << endl;
        return;
    }

    ProductoIngredienteArchivo piaux;

    for(Producto* prod : productos) {
        // Solo guardar ingredientes de productos normales
        if(prod->getTipo() == 'N') {
            vector<Ingrediente*> ings = prod->getIngredientes();

            for(Ingrediente* ing : ings) {
                piaux.codigo_producto = prod->getCodigo();
                piaux.codigo_ingrediente = ing->getCodigo();

                archiPI.write((char*)&piaux, sizeof(ProductoIngredienteArchivo));
            }
        }
    }

    archiPI.close();

    // ========== ARCHIVO 4: PRODUCTOS_COMPUESTOS ==========
    ofstream archiPC(archProductosCompuestos, ios::binary);

    if(!archiPC.is_open()) {
        cout << "Error al crear " << archProductosCompuestos << endl;
        return;
    }

    ProductoCompuestoArchivo pcaux;

    for(Producto* prod : productos) {
        if(prod->getTipo() == 'C') {
            ProductoCompuesto* pc = dynamic_cast<ProductoCompuesto*>(prod);
            vector<Producto*> productosContenidos = pc->getProductos();

            for(Producto* prodContenido : productosContenidos) {
                pcaux.codigo_producto_compuesto = prod->getCodigo();
                pcaux.codigo_producto_contenido = prodContenido->getCodigo();

                archiPC.write((char*)&pcaux, sizeof(ProductoCompuestoArchivo));
            }
        }
    }

    archiPC.close();
}

// ========== LEER ARCHIVOS BINARIOS ==========

void Gestora::leerArchivos(char* archProductos,
                           char* archIngredientes,
                           char* archProductosIngredientes,
                           char* archProductosCompuestos) {

    // ========== LEER INGREDIENTES PRIMERO ==========
    ifstream archiI(archIngredientes, ios::binary);

    if(archiI.is_open()) {
        IngredienteArchivo iaux;

        while(archiI.read((char*)&iaux, sizeof(IngredienteArchivo))) {
            Ingrediente* ing = new Ingrediente(iaux.codigo, iaux.nombre);
            ingredientes.push_back(ing);
        }

        archiI.close();
    }

    // ========== LEER PRODUCTOS ==========
    ifstream archiP(archProductos, ios::binary);

    if(archiP.is_open()) {
        ProductoArchivo paux;

        while(archiP.read((char*)&paux, sizeof(ProductoArchivo))) {
            Producto* producto;

            if(paux.tipo == 'C') {
                producto = new ProductoCompuesto(paux.codigo, paux.nombre);
            } else {
                producto = new Producto(paux.codigo, paux.nombre);
            }

            productos.push_back(producto);
        }

        archiP.close();
    }

    // ========== LEER PRODUCTOS_INGREDIENTES ==========
    ifstream archiPI(archProductosIngredientes, ios::binary);

    if(archiPI.is_open()) {
        ProductoIngredienteArchivo piaux;

        while(archiPI.read((char*)&piaux, sizeof(ProductoIngredienteArchivo))) {
            Producto* producto = buscarProducto(piaux.codigo_producto);
            Ingrediente* ingrediente = buscarIngrediente(piaux.codigo_ingrediente);

            if(producto != nullptr && ingrediente != nullptr && producto->getTipo() == 'N') {
                // Crear una copia del ingrediente para el producto
                Ingrediente* ingCopia = new Ingrediente(ingrediente->getCodigo(), ingrediente->getNombre());
                producto->agregarIngrediente(ingCopia);
            }
        }

        archiPI.close();
    }

    // ========== LEER PRODUCTOS_COMPUESTOS ==========
    ifstream archiPC(archProductosCompuestos, ios::binary);

    if(archiPC.is_open()) {
        ProductoCompuestoArchivo pcaux;

        while(archiPC.read((char*)&pcaux, sizeof(ProductoCompuestoArchivo))) {
            Producto* productoCompuesto = buscarProducto(pcaux.codigo_producto_compuesto);
            Producto* productoContenido = buscarProducto(pcaux.codigo_producto_contenido);

            if(productoCompuesto != nullptr && productoContenido != nullptr && productoCompuesto->getTipo() == 'C') {
                ProductoCompuesto* pc = dynamic_cast<ProductoCompuesto*>(productoCompuesto);
                pc->agregarProducto(productoContenido);
            }
        }

        archiPC.close();
    }
}

// ========== PUNTO 3: MÉTODOS CON STL ==========

Ingrediente* Gestora::obtenerIngredienteMasUtilizado() {
    if(ingredientes.empty()) {
        return nullptr;
    }

    // Contar cuántas veces se usa cada ingrediente
    map<int, int> contadorIngredientes;

    for(Producto* prod : productos) {
        if(prod->getTipo() == 'N') {
            vector<Ingrediente*> ings = prod->getIngredientes();

            for(Ingrediente* ing : ings) {
                contadorIngredientes[ing->getCodigo()]++;
            }
        } else if(prod->getTipo() == 'C') {
            ProductoCompuesto* pc = dynamic_cast<ProductoCompuesto*>(prod);
            vector<Ingrediente*> ings = pc->obtenerIngredientesSinRepetir();

            for(Ingrediente* ing : ings) {
                contadorIngredientes[ing->getCodigo()]++;
            }
        }
    }

    // Encontrar el ingrediente más utilizado
    auto maxIt = max_element(contadorIngredientes.begin(), contadorIngredientes.end(),
                             [](pair<int, int> a, pair<int, int> b) {
                                 return a.second < b.second;
                             });

    if(maxIt == contadorIngredientes.end()) {
        return nullptr;
    }

    return buscarIngrediente(maxIt->first);
}

Producto* Gestora::obtenerProductoConMasIngredientes() {
    if(productos.empty()) {
        return nullptr;
    }

    // Encontrar el producto con más ingredientes
    auto maxIt = max_element(productos.begin(), productos.end(),
                             [](Producto* a, Producto* b) {
                                 int cantA, cantB;

                                 if(a->getTipo() == 'N') {
                                     cantA = a->getCantidadIngredientes();
                                 } else {
                                     ProductoCompuesto* pcA = dynamic_cast<ProductoCompuesto*>(a);
                                     cantA = pcA->obtenerIngredientesSinRepetir().size();
                                 }

                                 if(b->getTipo() == 'N') {
                                     cantB = b->getCantidadIngredientes();
                                 } else {
                                     ProductoCompuesto* pcB = dynamic_cast<ProductoCompuesto*>(b);
                                     cantB = pcB->obtenerIngredientesSinRepetir().size();
                                 }

                                 return cantA < cantB;
                             });

    return *maxIt;
}

// ========== PUNTO LIBRE: GUARDAR EN TEXTO ==========

void Gestora::guardarEnTexto(char* archivoTexto) {
    ofstream archivo(archivoTexto);

    if(!archivo.is_open()) {
        cout << "Error al crear " << archivoTexto << endl;
        return;
    }

    for(Producto* prod : productos) {
        if(prod->getTipo() == 'C') {
            ProductoCompuesto* pc = dynamic_cast<ProductoCompuesto*>(prod);
            archivo << *pc;
        } else {
            archivo << *prod;
        }
        archivo << endl;
    }

    archivo.close();
}
