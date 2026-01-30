#include "Usuario.h"
#include <cstring>

Usuario::Usuario() {
    codigo = 0;
    strcpy(nombre, "");
    cargo = nullptr;
}

Usuario::Usuario(int codigo, const char* nombre, Cargo* cargo) {
    this->codigo = codigo;
    strcpy(this->nombre, nombre);
    this->cargo = cargo;
}

Usuario::~Usuario() {
    // NO eliminamos cargo porque es gestionado por Gestora
}

int Usuario::getCodigo() const {
    return codigo;
}

const char* Usuario::getNombre() const {
    return nombre;
}

Cargo* Usuario::getCargo() const {
    return cargo;
}

int Usuario::getIdCargo() const {
    if(cargo != nullptr) {
        return cargo->getId();
    }
    return -1;
}

void Usuario::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Usuario::setNombre(const char* nombre) {
    strcpy(this->nombre, nombre);
}

void Usuario::setCargo(Cargo* cargo) {
    this->cargo = cargo;
}

bool Usuario::tienePermiso(const string& permiso) const {
    if(cargo != nullptr) {
        return cargo->tienePermiso(permiso);
    }
    return false;
}

int Usuario::getCantidadPermisos() const {
    if(cargo != nullptr) {
        return cargo->getCantidadPermisos();
    }
    return 0;
}
