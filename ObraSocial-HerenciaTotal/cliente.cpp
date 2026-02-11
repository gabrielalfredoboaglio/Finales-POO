#include "cliente.h"
#include <cstring>

using namespace std;

Cliente::Cliente() {
    id = 0;
    strcpy(nombre, "");
    cantidad = 0;
}

Cliente::~Cliente() {}

// Ejercicio 1: Verificar si tiene una prestación
bool Cliente::tienePrestacion(char* prestacion) {
    for(string& p : prestaciones) {
        if(p == string(prestacion)) {
            return true;
        }
    }
    return false;
}

int Cliente::getId() { return id; }
char* Cliente::getNombre() { return nombre; }
int Cliente::getCantidad() { return cantidad; }
vector<string> Cliente::getPrestaciones() { return prestaciones; }

void Cliente::setId(int i) { id = i; }
void Cliente::setNombre(char* nom) { strcpy(nombre, nom); }
void Cliente::setCantidad(int c) { cantidad = c; }
void Cliente::setPrestaciones(vector<string> p) { prestaciones = p; }
