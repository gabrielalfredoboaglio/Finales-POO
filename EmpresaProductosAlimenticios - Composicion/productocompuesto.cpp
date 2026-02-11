#include "productocompuesto.h"
#include <algorithm>
#include <set>
#include <iostream>

ProductoCompuesto::ProductoCompuesto() : Producto() {
}

ProductoCompuesto::ProductoCompuesto(int codigo, char* nombre) : Producto(codigo, nombre) {
}

ProductoCompuesto::~ProductoCompuesto() {
    // No eliminar productos porque pueden ser compartidos
    // Solo limpiamos el vector
    productos.clear();
}

vector<Producto*> ProductoCompuesto::getProductos() {
    return productos;
}

int ProductoCompuesto::getCantidadProductos() {
    return productos.size();
}

void ProductoCompuesto::agregarProducto(Producto* producto) {
    productos.push_back(producto);
}

char ProductoCompuesto::getTipo() {
    return 'C'; // Compuesto
}

vector<Ingrediente*> ProductoCompuesto::obtenerIngredientesSinRepetir() {
    vector<Ingrediente*> resultado;
    set<int> codigosIngredientes;

    // Recorrer todos los productos
    for(Producto* prod : productos) {
        vector<Ingrediente*> ings = prod->getIngredientes();
        
        for(Ingrediente* ing : ings) {
            // Si no está en el set, agregarlo
            if(codigosIngredientes.find(ing->getCodigo()) == codigosIngredientes.end()) {
                codigosIngredientes.insert(ing->getCodigo());
                resultado.push_back(ing);
            }
        }
    }

    return resultado;
}

// ========== agregar para punto libre ==========
ostream& operator<<(ostream& os, ProductoCompuesto& productoCompuesto) {
    os << "Producto Compuesto: " << productoCompuesto.getNombre() << " (Codigo: " << productoCompuesto.getCodigo() << ")" << endl;
    os << "Productos contenidos:" << endl;
    
    vector<Producto*> productos = productoCompuesto.getProductos();
    for(Producto* prod : productos) {
        os << "  - " << prod->getNombre() << " (Codigo: " << prod->getCodigo() << ")" << endl;
    }
    
    os << "Ingredientes (sin repetir):" << endl;
    vector<Ingrediente*> ings = productoCompuesto.obtenerIngredientesSinRepetir();
    for(Ingrediente* ing : ings) {
        os << "  - " << ing->getNombre() << " (Codigo: " << ing->getCodigo() << ")" << endl;
    }
    
    return os;
}
