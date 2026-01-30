#ifndef EMPLEADO_H
#define EMPLEADO_H




class Empleado
{    
private:
    double monto;
    char nombre[200];
    double sueldoNeto;
    int aniosAntiguedad;
    int empleadosACargo;

public:
    Empleado();
    virtual ~Empleado ();

    int getMonto();
    char * getNombre();
    double extracted();
    double getSueldoNeto();
    int getAniosAntiguedad();
    int getEmpleadosACargo();
    void setMonto(int m);
    void setNombre(char * nom);
    void setAniosAntiguedad(int a) ;
    void setSueldoNeto(double n);
    void setEmpleadosACargo(int e) ;
};

#endif // EMPLEADO_H
