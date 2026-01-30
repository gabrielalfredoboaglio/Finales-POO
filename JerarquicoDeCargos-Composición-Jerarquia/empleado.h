#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <vector>
using namespace std;

class Empleado {
private:
    int numero;
    char nombre[200];
    Empleado* responsable;  // Puntero al jefe directo
    vector<Empleado*> empleados_a_cargo;  // Personas que reportan a este empleado

public:
    Empleado();
    Empleado(int num, const char* nom);
    ~Empleado();

    // Getters
    int getNumero() const;
    char* getNombre();
    const char* getNombre() const;
    Empleado* getResponsable() const;
    int getCantidadACargo() const;
    const vector<Empleado*>& getEmpleadosACargo() const;

    // Setters
    void setNumero(int num);
    void setNombre(const char* nom);
    void setResponsable(Empleado* resp);

    // Métodos para gestionar jerarquía
    void agregarEmpleadoACargo(Empleado* emp);
};

#endif // EMPLEADO_H
