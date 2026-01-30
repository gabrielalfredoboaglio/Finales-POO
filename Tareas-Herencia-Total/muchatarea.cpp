#include "muchatarea.h"
#include <iostream>

MuchaTarea::MuchaTarea() {}

MuchaTarea::~MuchaTarea() {
    // Liberar memoria de todas las subtareas
    for (Tarea* t : subtareas) {
        delete t;
    }
}

char MuchaTarea::getTipo() {
    return 'M';
}

void MuchaTarea::ejecutar() {
    std::cout << "=== Ejecutando tarea compuesta: " << descripcion << " ===" << std::endl;
    std::cout << "Contiene " << subtareas.size() << " subtareas" << std::endl;

    // Ejecutar cada subtarea
    for (size_t i = 0; i < subtareas.size(); i++) {
        std::cout << "  [Subtarea " << (i+1) << "] ";
        subtareas[i]->ejecutar();
    }

    std::cout << "=== Fin de tarea compuesta ===" << std::endl;
}

void MuchaTarea::agregarSubtarea(Tarea* t) {
    if (t != nullptr) {
        subtareas.push_back(t);
    }
}

const std::vector<Tarea*>& MuchaTarea::getSubtareas() const {
    return subtareas;
}

int MuchaTarea::getCantidadSubtareas() const {
    return subtareas.size();
}
