#ifndef VECTORORDENADO_H
#define VECTORORDENADO_H

#include <iostream>
using namespace std;

// ========== EJERCICIO 4: Estructura template vector dinámico ordenado (sin STL) ==========

template<class T>
class VectorOrdenado {
private:
    T* datos;
    int cantidad;
    int capacidad;

    void redimensionar() {
        capacidad *= 2;
        T* nuevo = new T[capacidad];
        for(int i = 0; i < cantidad; i++) {
            nuevo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo;
    }

public:
    VectorOrdenado() {
        capacidad = 10;
        cantidad = 0;
        datos = new T[capacidad];
    }

    ~VectorOrdenado() {
        delete[] datos;
    }

    // Agregar un elemento de forma ordenada
    void agregar(T elemento) {
        if(cantidad >= capacidad) {
            redimensionar();
        }

        // Buscar posición donde insertar (mantener orden)
        int pos = 0;
        while(pos < cantidad && datos[pos] < elemento) {
            pos++;
        }

        // Desplazar elementos hacia la derecha
        for(int i = cantidad; i > pos; i--) {
            datos[i] = datos[i - 1];
        }

        datos[pos] = elemento;
        cantidad++;
    }

    // Eliminar un elemento por índice
    void eliminar(int indice) {
        if(indice < 0 || indice >= cantidad) {
            return;
        }

        // Desplazar elementos hacia la izquierda
        for(int i = indice; i < cantidad - 1; i++) {
            datos[i] = datos[i + 1];
        }

        cantidad--;
    }

    // Imprimir todos los elementos de forma ordenada
    void imprimir() {
        for(int i = 0; i < cantidad; i++) {
            cout << datos[i] << endl;
        }
    }

    int getCantidad() {
        return cantidad;
    }

    T getElemento(int indice) {
        return datos[indice];
    }
};

// Respuesta: Se debe sobreescribir el operador < (menor que) en el tipo T
// para poder comparar los elementos y mantener el orden en la estructura.

#endif // VECTORORDENADO_H
