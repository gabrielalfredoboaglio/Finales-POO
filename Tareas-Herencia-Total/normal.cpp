#include "normal.h"

Normal::Normal() {}

char Normal::getTipo()
{
         return 'N';
}

void Normal::ejecutar()
{
    cout<< this ->descripcion;
}
