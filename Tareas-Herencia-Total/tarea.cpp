#include "Tarea.h"

Tarea::Tarea() {
    strcpy(descripcion, "");
    strcpy(fecha, "");
    strcpy(hora, "");
    duracion = 0;
}

Tarea::~Tarea() {
    // Nada que liberar (arrays automáticos)
}

char* Tarea::getDescripcion() {
    return descripcion;
}

char* Tarea::getFecha() {
    return fecha;
}

char* Tarea::getHora() {
    return hora;
}

int Tarea::getDuracion() const {
    return duracion;
}

void Tarea::setDescripcion(const char* desc) {
    strcpy(descripcion, desc);
}

void Tarea::setFecha(const char* fec) {
    strcpy(fecha, fec);
}

void Tarea::setHora(const char* hor) {
    strcpy(hora, hor);
}

void Tarea::setDuracion(int dur) {
    duracion = dur;
}

TareaArchivo Tarea::getStr()
{
    TareaArchivo str;

    strcpy(str.descripcion, descripcion);
    strcpy(str.fecha, fecha);
    strcpy(str.hora, hora);
    str.duracion = duracion;
    str.tipo = getTipo();

    return str;
}

void Tarea::setStr(const TareaArchivo& str)
{
    strcpy(descripcion, str.descripcion);
    strcpy(fecha, str.fecha);
    strcpy(hora, str.hora);
    duracion = str.duracion;
}
