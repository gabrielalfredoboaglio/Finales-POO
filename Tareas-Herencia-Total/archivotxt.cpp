#include "archivotxt.h"
#include <fstream>
ArchivoTxt::ArchivoTxt() {}

char ArchivoTxt::getTipo()
{
    return 'A';
}

void ArchivoTxt::ejecutar()

{
    std::ofstream archi("dato.txt",std::ios::app);
    if (archi.is_open()) {
        archi << "Se ejecuto "<<this->descripcion <<std::endl;
        archi.close();
    }
}
