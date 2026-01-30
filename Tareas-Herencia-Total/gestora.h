#ifndef GESTORA_H
#define GESTORA_H

#include "Tarea.h"
#include "muchatarea.h"
#include <vector>
#include <string>
#include <utility>  // Para std::pair

class Gestora {
private:
    std::vector<Tarea*> tareas;

    // Métodos privados para manejar MuchaTarea
    void guardarMuchaTarea( MuchaTarea* mt, std::ofstream& archi);
    MuchaTarea* leerMuchaTarea(std::ifstream& archi);

public:
    Gestora();
    ~Gestora();  // Destructor para liberar memoria

    void add(Tarea* t);
    void leer();
    void guardar();

    // Métodos STL
    std::vector<Tarea*> mayor();
    std::string dia();
    std::vector<std::pair<Tarea*, Tarea*>> obtenerTareasSuperpuestas();
};

#endif // GESTORA_H
