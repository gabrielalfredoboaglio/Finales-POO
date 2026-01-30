#ifndef NORMAL_H
#define NORMAL_H
#include "tarea.h"
#include <iostream>

using namespace std;
class Normal: public Tarea
{
public:

    Normal();
    char getTipo() ;  // ← AGREGAR
    void ejecutar();

};

#endif // NORMAL_H
