#ifndef CARGOEXTENDIDO_H
#define CARGOEXTENDIDO_H

#include "Cargo.h"

class CargoExtendido : public Cargo {
private:
    Cargo* cargo_base;  // Cargo del cual extiende (ej: Vendedor)
    // Los permisos adicionales se guardan en el vector 'permisos' heredado

public:
    CargoExtendido();
    CargoExtendido(int id, const char* nombre, Cargo* base);
    ~CargoExtendido();

    // Getters
    Cargo* getCargoBase() const;
    int getIdCargoBase() const;

    // Setters
    void setCargoBase(Cargo* base);

    // Métodos sobrescritos
    vector<string> getPermisos() const override;  // Combina base + adicionales
    bool tienePermiso(const string& permiso) const;
    char getTipo() const override;
    int getCantidadPermisos() const;
};

#endif // CARGOEXTENDIDO_H
