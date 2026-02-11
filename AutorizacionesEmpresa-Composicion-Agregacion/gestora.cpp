#include "Gestora.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    // Liberar memoria de cargos
    for(Cargo* c : cargos) {
        delete c;
    }

    // Liberar memoria de usuarios
    for(Usuario* u : usuarios) {
        delete u;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Cargo* Gestora::buscarCargo(int id) {
    for(Cargo* c : cargos) {
        if(c->getId() == id) {
            return c;
        }
    }
    return nullptr;
}

Usuario* Gestora::buscarUsuario(int codigo) {
    for(Usuario* u : usuarios) {
        if(u->getCodigo() == codigo) {
            return u;
        }
    }
    return nullptr;
}


// ========== PUNTO 1: GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(const char* archCargos,
                              const char* archPermisos,
                              const char* archUsuarios) {

    // ========== ARCHIVO 1: CARGOS ==========
    ofstream archiC(archCargos, ios::binary);

    if(!archiC.is_open()) {
        cout << "Error al crear " << archCargos << endl;
        return;
    }

    CargoArchivo caux;

    for(Cargo* c : cargos) {
        caux.id = c->getId();
        strcpy(caux.nombre, c->getNombre());
        caux.tipo = c->getTipo();

        // ========== LIBRE: Guardar id del cargo base si es extendido ==========
        if(c->getTipo() == 'E') {
            CargoExtendido* ce = dynamic_cast<CargoExtendido*>(c);
            caux.id_cargo_base = ce->getIdCargoBase();
        } else {
            caux.id_cargo_base = -1;
        }

        archiC.write((char*)&caux, sizeof(CargoArchivo));
    }

    archiC.close();

    // ========== ARCHIVO 2: PERMISOS DE CARGOS ==========
    ofstream archiP(archPermisos, ios::binary);

    if(!archiP.is_open()) {
        cout << "Error al crear " << archPermisos << endl;
        return;
    }

    PermisoCargo paux;

    for(Cargo* c : cargos) {
        // Para cargos extendidos, solo guardamos los permisos ADICIONALES
        vector<string> permisosAGuardar;

        // ========== LIBRE: Separar permisos propios de extendidos ==========
        if(c->getTipo() == 'E') {
            CargoExtendido* ce = dynamic_cast<CargoExtendido*>(c);
            vector<string> todos = ce->getPermisos();
            vector<string> base;

            if(ce->getCargoBase() != nullptr) {
                base = ce->getCargoBase()->getPermisos();
            }

            for(const string& p : todos) {
                if(find(base.begin(), base.end(), p) == base.end()) {
                    permisosAGuardar.push_back(p);
                }
            }
        } else {
            // Cargo normal: guardar todos
            permisosAGuardar = c->getPermisos();
        }

        // Guardar cada permiso
        for(const string& permiso : permisosAGuardar) {
            paux.id_cargo = c->getId();
            strcpy(paux.permiso, permiso.c_str());
            archiP.write((char*)&paux, sizeof(PermisoCargo));
        }
    }

    archiP.close();

    // ========== ARCHIVO 3: USUARIOS ==========
    ofstream archiU(archUsuarios, ios::binary);

    if(!archiU.is_open()) {
        cout << "Error al crear " << archUsuarios << endl;
        return;
    }

    UsuarioArchivo uaux;

    for(Usuario* u : usuarios) {
        uaux.codigo = u->getCodigo();
        strcpy(uaux.nombre, u->getNombre());
        uaux.id_cargo = u->getIdCargo();

        archiU.write((char*)&uaux, sizeof(UsuarioArchivo));
    }

    archiU.close();
}

// ========== LEER ARCHIVOS BINARIOS ==========

void Gestora::leerArchivos(const char* archCargos,
                           const char* archPermisos,
                           const char* archUsuarios) {

    // ========== LEER CARGOS ==========
    ifstream archiC(archCargos, ios::binary);

    if(!archiC.is_open()) {
        cout << "Error al abrir " << archCargos << endl;
        return;
    }

    CargoArchivo caux;

    while(archiC.read((char*)&caux, sizeof(CargoArchivo))) {
        Cargo* cargo;

        // ========== LIBRE: Crear CargoExtendido si tipo es 'E' ==========
        if(caux.tipo == 'E') {
            cargo = new CargoExtendido(caux.id, caux.nombre, nullptr);
        } else {
            cargo = new Cargo(caux.id, caux.nombre);
        }

        cargos.push_back(cargo);
    }

    archiC.close();

    // ========== LIBRE: Establecer relaciones de cargo_base ==========
    archiC.open(archCargos, ios::binary);

    while(archiC.read((char*)&caux, sizeof(CargoArchivo))) {
        if(caux.tipo == 'E' && caux.id_cargo_base != -1) {
            Cargo* cargoExt = buscarCargo(caux.id);
            Cargo* cargoBase = buscarCargo(caux.id_cargo_base);

            if(cargoExt != nullptr && cargoBase != nullptr) {
                CargoExtendido* ce = dynamic_cast<CargoExtendido*>(cargoExt);
                ce->setCargoBase(cargoBase);
            }
        }
    }

    archiC.close();

    // ========== LEER PERMISOS ==========
    ifstream archiP(archPermisos, ios::binary);

    if(!archiP.is_open()) {
        cout << "Error al abrir " << archPermisos << endl;
        return;
    }

    PermisoCargo paux;

    while(archiP.read((char*)&paux, sizeof(PermisoCargo))) {
        Cargo* cargo = buscarCargo(paux.id_cargo);

        if(cargo != nullptr) {
            cargo->agregarPermiso(paux.permiso);
        }
    }

    archiP.close();

    // ========== LEER USUARIOS ==========
    ifstream archiU(archUsuarios, ios::binary);

    if(!archiU.is_open()) {
        cout << "Error al abrir " << archUsuarios << endl;
        return;
    }

    UsuarioArchivo uaux;

    while(archiU.read((char*)&uaux, sizeof(UsuarioArchivo))) {
        Cargo* cargo = buscarCargo(uaux.id_cargo);

        Usuario* usuario = new Usuario(uaux.codigo, uaux.nombre, cargo);
        usuarios.push_back(usuario);
    }

    archiU.close();
}

// ========== PUNTO 2: VERIFICAR PERMISO ==========

bool Gestora::usuarioTienePermiso(int codigoUsuario, const string& permiso) {
    Usuario* usuario = buscarUsuario(codigoUsuario);

    if(usuario == nullptr) {
        return false;
    }

    return usuario->tienePermiso(permiso);
}

// ========== PUNTO 3: MÉTODOS CON STL ==========

// 3.1: Cargos con más permisos
vector<Cargo*> Gestora::obtenerCargosMasPermisos() {
    if(cargos.empty()) {
        return vector<Cargo*>();
    }

    // 1. Encontrar el máximo
    auto maxIt = max_element(cargos.begin(), cargos.end(),
                             [](Cargo* a, Cargo* b) {
                                 return a->getCantidadPermisos() < b->getCantidadPermisos();
                             });

    int maxPermisos = (*maxIt)->getCantidadPermisos();

    // 2. Recolectar todos los que tienen ese máximo
    vector<Cargo*> resultado;

    for(Cargo* c : cargos) {
        if(c->getCantidadPermisos() == maxPermisos) {
            resultado.push_back(c);
        }
    }

    return resultado;
}

// 3.2: Permisos que están en varios cargos
vector<string> Gestora::obtenerPermisosEnVariosCargos() {
    // 1. Contar en cuántos cargos aparece cada permiso
    map<string, int> contadorPermisos;

    for(Cargo* c : cargos) {
        vector<string> permisos = c->getPermisos();

        // Marcar cada permiso único de este cargo
        // Usar un set para evitar contar el mismo permiso dos veces del mismo cargo
        set<string> permisosUnicos(permisos.begin(), permisos.end());

        for(const string& p : permisosUnicos) {
            contadorPermisos[p]++;
        }
    }

    // 2. Filtrar los que aparecen en 2 o más cargos
    vector<string> resultado;

    for(const auto& par : contadorPermisos) {
        if(par.second >= 2) {
            resultado.push_back(par.first);
        }
    }

    return resultado;
}

// 3.3: Usuarios con más permisos
vector<Usuario*> Gestora::obtenerUsuariosMasPermisos() {
    if(usuarios.empty()) {
        return vector<Usuario*>();
    }

    // 1. Encontrar el máximo
    auto maxIt = max_element(usuarios.begin(), usuarios.end(),
                             [](Usuario* a, Usuario* b) {
                                 return a->getCantidadPermisos() < b->getCantidadPermisos();
                             });

    int maxPermisos = (*maxIt)->getCantidadPermisos();

    // 2. Recolectar todos los que tienen ese máximo
    vector<Usuario*> resultado;

    for(Usuario* u : usuarios) {
        if(u->getCantidadPermisos() == maxPermisos) {
            resultado.push_back(u);
        }
    }

    return resultado;
}

