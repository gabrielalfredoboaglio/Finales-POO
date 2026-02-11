#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <cstring>
#include <vector>
using namespace std;

class Empleado {
private:
    int id;
    char nombre[200];
    double sueldoNeto;
    int aniosAntiguedad;
    int empleadosACargo;
    // ========== agregar para punto libre ==========
    vector<char> tiposItems;  // Tipos de items que aplican a este empleado

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

    // ========== agregar para punto libre ==========
    void agregarTipoItem(char tipo);
    vector<char> getTiposItems();
    bool tieneItem(char tipo);
};

#endif