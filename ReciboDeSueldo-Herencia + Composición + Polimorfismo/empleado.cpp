#include "empleado.h"
#include <cstring>

using namespace std;

Empleado::Empleado() {
    id = 0;
    strcpy(nombre, "");
    sueldoNeto = 0;
    aniosAntiguedad = 0;
    empleadosACargo = 0;
}

Empleado::~Empleado() {}

int Empleado::getId() { return id; }
char* Empleado::getNombre() { return nombre; }
double Empleado::getSueldoNeto() { return sueldoNeto; }
int Empleado::getAniosAntiguedad() { return aniosAntiguedad; }
int Empleado::getEmpleadosACargo() { return empleadosACargo; }

void Empleado::setId(int i) { id = i; }
void Empleado::setNombre(char* nom) { strcpy(nombre, nom); }
void Empleado::setSueldoNeto(double n) { sueldoNeto = n; }
void Empleado::setAniosAntiguedad(int a) { aniosAntiguedad = a; }
void Empleado::setEmpleadosACargo(int e) { empleadosACargo = e; }

// ========== agregar para punto libre ==========
void Empleado::agregarTipoItem(char tipo) {
    tiposItems.push_back(tipo);
}

vector<char> Empleado::getTiposItems() {
    return tiposItems;
}

bool Empleado::tieneItem(char tipo) {
    for(char t : tiposItems) {
        if(t == tipo) return true;
    }
    return false;
}