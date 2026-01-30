#include "empleado.h"
#include <cstring>



Empleado::Empleado() {
    sueldoNeto = 0;
    strcpy(nombre, "");
    aniosAntiguedad = 0;
    empleadosACargo = 0;
}

int Empleado::getMonto()
{
    return monto;
}

char *Empleado::getNombre()
{
    return nombre;
}

double Empleado::getSueldoNeto()
{
    return sueldoNeto;
}

int Empleado::getAniosAntiguedad()
{
    return aniosAntiguedad;
}

int Empleado::getEmpleadosACargo()
{
    return empleadosACargo;
}

void Empleado::setMonto(int m)
{
    this -> monto = m;
}

void Empleado::setNombre(char *nom)
{
    strcpy(nombre, nom);
}

void Empleado::setAniosAntiguedad(int a)
{
    this->aniosAntiguedad = a;
}
void Empleado::setSueldoNeto(double n)
{
    this ->sueldoNeto = n;
}

void Empleado::setEmpleadosACargo(int e)
{
    this->empleadosACargo =e;
}

