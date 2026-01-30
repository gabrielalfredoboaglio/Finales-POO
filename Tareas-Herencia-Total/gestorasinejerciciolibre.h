#ifndef GESTORA_H
#define GESTORA_H

#include "Tarea.h"
#include <vector>
#include <string>
#include <utility>  // Para std::pair

class Gestora {
private:
    std::vector<Tarea*> tareas;

public:
    Gestora();
    ~Gestora();

    void add(Tarea* t);
    void leer();
    void guardar();

    // Métodos STL
    std::vector<Tarea*> mayor();
    std::string dia();
    std::vector<std::pair<Tarea*, Tarea*>> obtenerTareasSuperpuestas();
};

#endif // GESTORA_H
