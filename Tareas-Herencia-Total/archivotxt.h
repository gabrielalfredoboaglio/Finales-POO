#ifndef ARCHIVOTXT_H
#define ARCHIVOTXT_H

#include "Tarea.h"


class ArchivoTxt  : public Tarea
{
public:
    ArchivoTxt();
    char getTipo();
    void ejecutar();
};

#endif // ARCHIVOTXT_H
