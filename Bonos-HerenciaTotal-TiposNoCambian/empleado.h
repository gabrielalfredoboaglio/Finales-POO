#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
using namespace std;

class empleado{

protected:
int nro;
char nombre[200];
double ventas;
double porcentaje;


public:

    empleado();
    virtual char getTipo() = 0;
    virtual ~empleado ();
    int getNro();
    char * getNombre();
    virtual double getVentas();
    double getPorcentaje();
    void setNro(int n);
    void setNombre(char * nom);
    void setPorcentaje(double p) ;
    void setVentas(double v);

    friend ostream& operator<<(ostream& os, empleado& e);
    virtual double calcularBono()= 0;
};




#endif // EMPLEADO_H
