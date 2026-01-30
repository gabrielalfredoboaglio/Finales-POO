#ifndef MUCHATAREA_H
#define MUCHATAREA_H

#include "Tarea.h"
#include <vector>

class MuchaTarea : public Tarea {
private:
    std::vector<Tarea*> subtareas;

public:
    MuchaTarea();
    ~MuchaTarea();

    char getTipo() override;
    void ejecutar() override;

    // Métodos específicos para manejar subtareas
    void agregarSubtarea(Tarea* t);
    const std::vector<Tarea*>& getSubtareas() const;
    int getCantidadSubtareas() const;
};

#endif // MUCHATAREA_H
