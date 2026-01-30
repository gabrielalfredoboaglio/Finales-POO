#ifndef USUARIO_H
#define USUARIO_H

#include "Cargo.h"

class Usuario {
private:
    int codigo;
    char nombre[200];
    Cargo* cargo;

public:
    Usuario();
    Usuario(int codigo, const char* nombre, Cargo* cargo);
    ~Usuario();

    // Getters
    int getCodigo() const;
    const char* getNombre() const;
    Cargo* getCargo() const;
    int getIdCargo() const;

    // Setters
    void setCodigo(int codigo);
    void setNombre(const char* nombre);
    void setCargo(Cargo* cargo);

    // Método para verificar permisos
    bool tienePermiso(const string& permiso) const;
    int getCantidadPermisos() const;
};

#endif // USUARIO_H
