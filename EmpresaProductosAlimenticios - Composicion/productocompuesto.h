#ifndef PRODUCTOCOMPUESTO_H
#define PRODUCTOCOMPUESTO_H

#include "producto.h"
#include <vector>
#include <iostream>
using namespace std;

class ProductoCompuesto : public Producto {
private:
    vector<Producto*> productos;

public:
    ProductoCompuesto();
    ProductoCompuesto(int codigo, char* nombre);
    ~ProductoCompuesto();

    vector<Producto*> getProductos();
    int getCantidadProductos();
    void agregarProducto(Producto* producto);
    char getTipo();
    vector<Ingrediente*> obtenerIngredientesSinRepetir();

    friend ostream& operator<<(ostream& os, ProductoCompuesto& productoCompuesto);
};

#endif // PRODUCTOCOMPUESTO_H
