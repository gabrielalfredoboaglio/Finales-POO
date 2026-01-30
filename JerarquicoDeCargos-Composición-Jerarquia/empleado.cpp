#include "Empleado.h"
#include <cstring>

Empleado::Empleado() {
    numero = 0;
    strcpy(nombre, "");
    responsable = nullptr;
}

Empleado::Empleado(int num, const char* nom) {
    numero = num;
    strcpy(nombre, nom);
    responsable = nullptr;
}

Empleado::~Empleado() {
    // No eliminamos empleados_a_cargo ni responsable porque son gestionados por Gestora
}

int Empleado::getNumero() const {
    return numero;
}

char* Empleado::getNombre() {
    return nombre;
}

const char* Empleado::getNombre() const {
    return nombre;
}

Empleado* Empleado::getResponsable() const {
    return responsable;
}

int Empleado::getCantidadACargo() const {
    return empleados_a_cargo.size();
}

const vector<Empleado*>& Empleado::getEmpleadosACargo() const {
    return empleados_a_cargo;
}

void Empleado::setNumero(int num) {
    numero = num;
}

void Empleado::setNombre(const char* nom) {
    strcpy(nombre, nom);
}

void Empleado::setResponsable(Empleado* resp) {
    responsable = resp;
}

void Empleado::agregarEmpleadoACargo(Empleado* emp) {
    if(emp != nullptr) {
        empleados_a_cargo.push_back(emp);
        emp->setResponsable(this);  // Establecer relación bidireccional
    }
}
