#ifndef TAREA_H
#define TAREA_H

#include <iostream>
#include <cstring>

using namespace std;

struct TareaArchivo {
    char descripcion[200];
    char fecha[8];
    char hora[6];
    int duracion;
    char tipo;
};

// ========== LIBRE: Struct para tarea compuesta ==========
struct TareaCompuestaArchivo {
    TareaArchivo datosPrincipal;
    int cantidadSubtareas;
};

class Tarea {
protected:
    char descripcion[200];  // ← Arrays (como siempre)
    char fecha[8];
    char hora[6];
    int duracion;

public:
    Tarea();
    virtual ~Tarea();

    virtual char getTipo() = 0;
    char* getDescripcion();
    char* getFecha();
    char* getHora();
    int getDuracion() const;
    TareaArchivo getStr();
    void setDescripcion(const char* desc);
    void setFecha(const char* fec);
    void setHora(const char* hor);
    void setDuracion(int dur);
    void setStr(const TareaArchivo& str);
    virtual void ejecutar() = 0;  // Polimorfismo

};

#endif
