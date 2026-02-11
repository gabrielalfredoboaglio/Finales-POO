#ifndef GESTORA_H
#define GESTORA_H

#include "Usuario.h"
#include "Cargo.h"
// Libre: include de CargoExtendido
#include "CargoExtendido.h"
#include <vector>
#include <string>
using namespace std;

// ========== STRUCTS PARA ARCHIVOS BINARIOS ==========

// Archivo: cargos.dat
struct CargoArchivo {
    int id;
    char nombre[200];
    char tipo;  // Libre: 'N' = Normal, 'E' = Extendido
    int id_cargo_base;  // Libre: Solo para CargoExtendido, -1 si es Normal
};

// Archivo: permisos_cargo.dat
struct PermisoCargo {
    int id_cargo;
    char permiso[200];
};

// Archivo: usuarios.dat
struct UsuarioArchivo {
    int codigo;
    char nombre[200];
    int id_cargo;
};

// ========== CLASE GESTORA ==========

class Gestora {
private:
    vector<Cargo*> cargos;
    vector<Usuario*> usuarios;

    // Métodos auxiliares privados
    Cargo* buscarCargo(int id);
    Usuario* buscarUsuario(int codigo);

public:
    Gestora();
    ~Gestora();



    // PUNTO 1: Guardar en archivos binarios
    void guardarArchivos(const char* archCargos,
                         const char* archPermisos,
                         const char* archUsuarios);

    // Métodos para leer archivos binarios
    void leerArchivos(const char* archCargos,
                      const char* archPermisos,
                      const char* archUsuarios);

    // PUNTO 2: Verificar si usuario tiene permiso
    bool usuarioTienePermiso(int codigoUsuario, const string& permiso);

    // PUNTO 3: Métodos con STL

    // 3.1: Cargos con más permisos
    vector<Cargo*> obtenerCargosMasPermisos();

    // 3.2: Permisos que están en varios cargos
    vector<string> obtenerPermisosEnVariosCargos();

    // 3.3: Usuarios con más permisos
    vector<Usuario*> obtenerUsuariosMasPermisos();


};

#endif // GESTORA_H
