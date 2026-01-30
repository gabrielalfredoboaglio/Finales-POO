#include "empleado.h"
#include <cstring>


empleado::empleado() {
    nro = 0;
    strcpy(nombre, "");
    ventas = 0;
    porcentaje = 0;
}


empleado::~empleado()
{

}

int empleado::getNro()
{
    return nro;
}

char *empleado::getNombre()
{
    return nombre;
}

double empleado::getVentas()
{
 return ventas;
}


void empleado::setNro(int n)
{
    this-> nro = n ;
}


void empleado::setPorcentaje(double p)
{
    this -> porcentaje = p;
}

void empleado::setNombre(char * nom)
{
  strcpy(nombre, nom);
}
double empleado::getPorcentaje() {
    return porcentaje;
}

ostream& operator<<(ostream& os, empleado& e) {
    os << e.getNro() << " - "
       << e.getNombre() << " - $"
       << e.calcularBono();
    return os;
}
