#ifndef CARGO_H
#define CARGO_H

#include <vector>
#include <string>
using namespace std;

class Cargo {
protected:
    int id;
    char nombre[200];
    vector<string> permisos;

public:
    Cargo();
    Cargo(int id, const char* nombre);
    virtual ~Cargo();

    // Getters
    int getId() const;
    const char* getNombre() const;
    virtual vector<string> getPermisos() const;
    virtual int getCantidadPermisos() const;

    // Setters
    void setId(int id);
    void setNombre(const char* nombre);

    // Métodos para gestionar permisos
    void agregarPermiso(const string& permiso);
    virtual bool tienePermiso(const string& permiso) const;

    // Para identificar el tipo de cargo
    virtual char getTipo() const;
};

#endif // CARGO_H
