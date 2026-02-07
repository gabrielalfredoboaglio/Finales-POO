#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#include <string>
using namespace std;

class Ingrediente {
private:
    int codigo;
    char nombre[200];

public:
    Ingrediente();
    Ingrediente(int codigo, char* nombre);
    ~Ingrediente();

    int getCodigo();
    char* getNombre();
    void setCodigo(int codigo);
    void setNombre(char* nombre);
};

#endif // INGREDIENTE_H
