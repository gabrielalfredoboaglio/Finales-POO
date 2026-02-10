#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <cstring>
using namespace std;

class Empleado {
private:
    int id;
    char nombre[200];
    double sueldoNeto;
    int aniosAntiguedad;
    int empleadosACargo;

public:
    Empleado();
    ~Empleado();

    int getId();
    char* getNombre();
    double getSueldoNeto();
    int getAniosAntiguedad();
    int getEmpleadosACargo();

    void setId(int i);
    void setNombre(char* nom);
    void setSueldoNeto(double n);
    void setAniosAntiguedad(int a);
    void setEmpleadosACargo(int e);
};

#endif