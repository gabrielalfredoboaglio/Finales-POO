#include "gestora.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

Gestora::Gestora() {
}

Gestora::~Gestora() {
    for(Producto* p : productos) {
        delete p;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Producto* Gestora::buscarProducto(char* nombre) {
    for(Producto* p : productos) {
        if(strcmp(p->getNombre(), nombre) == 0) {
            return p;
        }
    }
    return nullptr;
}

vector<Producto*> Gestora::getProductos() {
    return productos;
}

// ========== EJERCICIO 2: Leer archivo de texto ==========

void Gestora::leerArchivoTexto(char* archivo) {
    ifstream arch(archivo);
    string linea;
    Producto* productoActual = nullptr;
    Comentario* comentarioActual = nullptr;

    while(getline(arch, linea)) {
        if(linea.empty()) continue;

        int nivel = 0;
        int i = 0;
        while(i < linea.length() && linea[i] == '-') {
            nivel++;
            i++;
        }

        string contenido = linea.substr(nivel);
        while(!contenido.empty() && contenido[0] == ' ') {
            contenido = contenido.substr(1);
        }

        if(nivel == 0) {
            char nombre[200];
            strcpy(nombre, contenido.c_str());
            productoActual = new Producto(nombre);
            productos.push_back(productoActual);
            comentarioActual = nullptr;
        } else if(nivel == 1) {
            size_t pos = contenido.find(" : ");
            if(pos != string::npos) {
                string texto = contenido.substr(0, pos);
                string puntajeStr = contenido.substr(pos + 3);
                int puntaje = stoi(puntajeStr);

                char txt[500];
                strcpy(txt, texto.c_str());
                comentarioActual = new Comentario(txt, puntaje);
                productoActual->agregarComentario(comentarioActual);
            }
        } else if(nivel == 2) {
            if(comentarioActual != nullptr) {
                size_t pos = contenido.find(" : ");
                if(pos != string::npos) {
                    string texto = contenido.substr(0, pos);
                    string puntajeStr = contenido.substr(pos + 3);
                    int puntaje = stoi(puntajeStr);

                    char txt[500];
                    strcpy(txt, texto.c_str());
                    Comentario* hijo = new Comentario(txt, puntaje);
                    comentarioActual->agregarComentarioHijo(hijo);
                }
            }
        }
    }

    arch.close();
}

// ========== EJERCICIO 3: Métodos con STL ==========

vector<Producto*> Gestora::obtenerProductosMayorPuntaje() {
    if(productos.empty()) {
        return vector<Producto*>();
    }

    auto maxIt = max_element(productos.begin(), productos.end(),
        [](Producto* a, Producto* b) {
            return a->calcularPuntajePromedio() < b->calcularPuntajePromedio();
        });

    double maxPuntaje = (*maxIt)->calcularPuntajePromedio();

    vector<Producto*> resultado;
    copy_if(productos.begin(), productos.end(), back_inserter(resultado),
        [maxPuntaje](Producto* p) {
            return p->calcularPuntajePromedio() == maxPuntaje;
        });

    return resultado;
}

vector<Producto*> Gestora::obtenerProductosMasComentariosNegativos() {
    if(productos.empty()) {
        return vector<Producto*>();
    }

    auto maxIt = max_element(productos.begin(), productos.end(),
        [](Producto* a, Producto* b) {
            return a->contarComentariosNegativos() < b->contarComentariosNegativos();
        });

    int maxNegativos = (*maxIt)->contarComentariosNegativos();

    vector<Producto*> resultado;
    copy_if(productos.begin(), productos.end(), back_inserter(resultado),
        [maxNegativos](Producto* p) {
            return p->contarComentariosNegativos() == maxNegativos;
        });

    return resultado;
}

vector<Producto*> Gestora::obtenerProductosMasComentarios() {
    if(productos.empty()) {
        return vector<Producto*>();
    }

    auto maxIt = max_element(productos.begin(), productos.end(),
        [](Producto* a, Producto* b) {
            return a->contarTotalComentarios() < b->contarTotalComentarios();
        });

    int maxComentarios = (*maxIt)->contarTotalComentarios();

    vector<Producto*> resultado;
    copy_if(productos.begin(), productos.end(), back_inserter(resultado),
        [maxComentarios](Producto* p) {
            return p->contarTotalComentarios() == maxComentarios;
        });

    return resultado;
}

// ========== EJERCICIO 4: Guardar en archivo binario ==========

void Gestora::guardarArchivoBinario(char* archivo) {
    ofstream arch(archivo, ios::binary);

    if(!arch.is_open()) {
        cout << "Error al crear " << archivo << endl;
        return;
    }

    ProductoArchivo paux;

    vector<Producto*> mayorPuntaje = obtenerProductosMayorPuntaje();
    for(Producto* p : mayorPuntaje) {
        strcpy(paux.nombre, p->getNombre());
        paux.puntajePromedio = p->calcularPuntajePromedio();
        paux.comentariosNegativos = p->contarComentariosNegativos();
        paux.totalComentarios = p->contarTotalComentarios();

        arch.write((char*)&paux, sizeof(ProductoArchivo));
    }

    vector<Producto*> masNegativos = obtenerProductosMasComentariosNegativos();
    for(Producto* p : masNegativos) {
        strcpy(paux.nombre, p->getNombre());
        paux.puntajePromedio = p->calcularPuntajePromedio();
        paux.comentariosNegativos = p->contarComentariosNegativos();
        paux.totalComentarios = p->contarTotalComentarios();

        arch.write((char*)&paux, sizeof(ProductoArchivo));
    }

    vector<Producto*> masComentarios = obtenerProductosMasComentarios();
    for(Producto* p : masComentarios) {
        strcpy(paux.nombre, p->getNombre());
        paux.puntajePromedio = p->calcularPuntajePromedio();
        paux.comentariosNegativos = p->contarComentariosNegativos();
        paux.totalComentarios = p->contarTotalComentarios();

        arch.write((char*)&paux, sizeof(ProductoArchivo));
    }

    arch.close();
}
