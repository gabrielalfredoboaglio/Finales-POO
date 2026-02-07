#ifndef CONJUNTOPAQUETES_H
#define CONJUNTOPAQUETES_H

#include "paquete.h"
#include <vector>
using namespace std;

// ========== LIBRE: Clase ConjuntoPaquetes ==========

class ConjuntoPaquetes {
private:
    char codigo[100];
    char nombre[100];
    int version;
    vector<Paquete*> paquetes;

public:
    ConjuntoPaquetes();
    ConjuntoPaquetes(char* codigo, char* nombre, int version);
    ~ConjuntoPaquetes();

    char* getCodigo();
    char* getNombre();
    int getVersion();
    vector<Paquete*> getPaquetes();
    int getCantidadPaquetes();

    void setCodigo(char* codigo);
    void setNombre(char* nombre);
    void setVersion(int version);
    void agregarPaquete(Paquete* paquete);

    // Libre: Instalar todos los paquetes dependientes del conjunto
    vector<Paquete*> instalarDependientes();
};

#endif // CONJUNTOPAQUETES_H
