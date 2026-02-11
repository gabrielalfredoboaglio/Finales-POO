#include "Gestora.h"
#include "Vendedor.h"
#include "Jefe.h"
#include <fstream>
#include <algorithm>  // max_element, copy_if, count_if
#include <map>        // map
#include <string>     // string
#include <iterator>   // back_inserter
// Libre: include de EmpleadoMuchasVentas
#include "EmpleadoMuchasVentas.h"
using namespace std;

Gestora::Gestora() {
    // Constructor vacío
}

Gestora::~Gestora() {
    // Liberar memoria de empleados
    for(empleado* e : empleados) {
        delete e;
    }
}

// ========== PUNTO 2: LEER ARCHIVOS ==========
void Gestora::leerArchivos() {
    // ========== LEER EMPLEADO.DAT ==========
    ifstream archiEmpleados("Empleado.dat", ios::binary);
    EmpleadoArchivo eaux;
    empleado* emp;

    if(!archiEmpleados.is_open()) return;

    while(archiEmpleados.read((char*)&eaux, sizeof(EmpleadoArchivo))) {
        // Crear empleado según tipo
        switch(eaux.tipo) {
        case 'V':
            emp = new vendedor();
            break;
        case 'J':
            emp = new Jefe();
            break;
        // ========== LIBRE: Nuevo tipo EmpleadoMuchasVentas ==========
        case 'M':
            emp = new empleadoMuchasVentas();
            break;
        default:
            continue;  // Tipo inválido, saltar
        }

        // Copiar datos del struct al objeto
        emp->setNro(eaux.nro);
        emp->setNombre(eaux.nombre);
        emp->setVentas(eaux.ventas);
        emp->setPorcentaje(eaux.porcentaje);

        empleados.push_back(emp);
    }
    archiEmpleados.close();

    // ========== LEER JEFE.DAT ==========
    ifstream archiJefes("Jefe.dat", ios::binary);
    JefeArchivo jaux;

    if(!archiJefes.is_open()) return;

    while(archiJefes.read((char*)&jaux, sizeof(JefeArchivo))) {
        // Buscar el jefe
        empleado* jefe = buscarEmpleado(jaux.nro_jefe);

        // Buscar el empleado
        empleado* empleado = buscarEmpleado(jaux.nro_empleado);

        // Convertir a Jefe* para llamar agregarEmpleado
        Jefe* j = dynamic_cast<Jefe*>(jefe);

        if(j != nullptr && empleado != nullptr) {
            j->agregarEmpleado(empleado);
        }
    }
    archiJefes.close();


    // ========== LIBRE: LEER VENTAS.DAT ==========
    ifstream archiVentas("ventas.dat", ios::binary);
    VentaEmpleadoArchivo vaux;

    if(!archiVentas.is_open()) return;

    while(archiVentas.read((char*)&vaux, sizeof(VentaEmpleadoArchivo))) {
        // Buscar el empleado
        empleado* emp = buscarEmpleado(vaux.nro_empleado);

        // Verificar si es EmpleadoMuchasVentas
        empleadoMuchasVentas* empMV = dynamic_cast<empleadoMuchasVentas*>(emp);

        if(empMV != nullptr) {
            empMV->agregarVenta(vaux.monto_venta);
        }
    }
    archiVentas.close();
}


// ========== MÉTODO AUXILIAR PRIVADO ==========
empleado* Gestora::buscarEmpleado(int nro) {
    for(empleado* e : empleados) {
        if(e->getNro() == nro) {
            return e;
        }
    }
    return nullptr;
}

// ========== PUNTO 3: GUARDAR ARCHIVO DE TEXTO  ==========
void Gestora::guardarArchivoTexto() {
    ofstream archi("empleados_bonos.txt");

    if(!archi.is_open()) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    // Escribir cada empleado usando el operador
    for(empleado* e : empleados) {
        archi << *e << endl;  // ← Usa el operador sobrecargado
    }

    archi.close();
}


// ========== PUNTO 4: MÉTODOS CON STL (esqueleto) ==========
vector<empleado*> Gestora::obtenerEmpleadosMayorBono() {
    if(empleados.empty()) {
        return vector<empleado*>();
    }

    // 1. Ordenar de MAYOR a MENOR por bono
    sort(empleados.begin(), empleados.end(),
         [](empleado* a, empleado* b) {
             return a->calcularBono() > b->calcularBono();
         });

    // 2. El primero tiene el bono máximo
    double maxBono = empleados.front()->calcularBono();

    // 3. Agregar todos con ese bono (están al principio)
    vector<empleado*> resultado;
    for(empleado* e : empleados) {
        if(e->calcularBono() == maxBono) {
            resultado.push_back(e);
        } else {
            break;  // Ya no hay más con ese bono
        }
    }

    return resultado;
}

vector<empleado*> Gestora::obtenerJefesMasEmpleados() {
    // 1. Filtrar solo jefes
    vector<Jefe*> jefes;
    for(empleado* e : empleados) {
        if(e->getTipo() == 'J') {
            Jefe* j = dynamic_cast<Jefe*>(e);
            if(j != nullptr) {
                jefes.push_back(j);
            }
        }
    }

    if(jefes.empty()) {
        return vector<empleado*>();
    }

    // 2. Ordenar de MAYOR a MENOR por cantidad de empleados
    sort(jefes.begin(), jefes.end(),
         [](Jefe* a, Jefe* b) {
             return a->getCantidadEmpleados() > b->getCantidadEmpleados();
         });

    // 3. El primero tiene la cantidad máxima
    int maxCantidad = jefes.front()->getCantidadEmpleados();

    // 4. Agregar todos con esa cantidad
    vector<empleado*> resultado;
    for(Jefe* j : jefes) {
        if(j->getCantidadEmpleados() == maxCantidad) {
            resultado.push_back(j);
        } else {
            break;
        }
    }

    return resultado;
}

vector<string> Gestora::obtenerNombresRepetidos() {
    // 1. Contar nombres
    map<string, int> contadorNombres;
    for(empleado* e : empleados) {
        contadorNombres[string(e->getNombre())]++;
    }

    // 2. Encontrar máximo
    auto maxIt = max_element(contadorNombres.begin(), contadorNombres.end(),
                             [](const auto& a, const auto& b) {
                                 return a.second < b.second;
                             });
    int maxRepeticiones = maxIt->second;

    // 3. Llenar resultado
    vector<string> resultado;  // ← Vector VACÍO al principio

    for(const auto& par : contadorNombres) {
        if(par.second == maxRepeticiones && par.second > 1) {
            resultado.push_back(par.first);  // ← ACÁ se agrega
        }
    }

    return resultado;  // ← Devolver vector (puede tener 0, 1 o más elementos)
}
