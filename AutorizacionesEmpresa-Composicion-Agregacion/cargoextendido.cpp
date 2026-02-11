// ========== LIBRE: Implementación CargoExtendido ==========
#include "CargoExtendido.h"
#include <algorithm>

CargoExtendido::CargoExtendido() : Cargo() {
    cargo_base = nullptr;
}

CargoExtendido::CargoExtendido(int id, const char* nombre, Cargo* base)
    : Cargo(id, nombre) {
    cargo_base = base;
}

CargoExtendido::~CargoExtendido() {
    // NO eliminamos cargo_base porque es gestionado por Gestora
}

Cargo* CargoExtendido::getCargoBase() const {
    return cargo_base;
}

int CargoExtendido::getIdCargoBase() const {
    if(cargo_base != nullptr) {
        return cargo_base->getId();
    }
    return -1;
}

void CargoExtendido::setCargoBase(Cargo* base) {
    cargo_base = base;
}

vector<string> CargoExtendido::getPermisos() const {
    vector<string> todos;

    // 1. Obtener permisos del cargo base (si existe)
    if(cargo_base != nullptr) {
        vector<string> permisos_base = cargo_base->getPermisos();
        todos.insert(todos.end(), permisos_base.begin(), permisos_base.end());
    }

    // 2. Agregar permisos adicionales (los propios)
    todos.insert(todos.end(), permisos.begin(), permisos.end());

    return todos;
}

bool CargoExtendido::tienePermiso(const string& permiso) const {
    // Buscar en permisos propios
    if(find(permisos.begin(), permisos.end(), permiso) != permisos.end()) {
        return true;
    }

    // Buscar en permisos del cargo base
    if(cargo_base != nullptr) {
        return cargo_base->tienePermiso(permiso);
    }

    return false;
}

char CargoExtendido::getTipo() const {
    return 'E';  // 'E' = Extendido
}

int CargoExtendido::getCantidadPermisos() const {
    return getPermisos().size();
}
