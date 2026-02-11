#include "gestora.h"
#include "monto.h"
#include "antiguedad.h"
#include "empleadoacargo.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

Gestora::Gestora() {
    // Ejercicio 1: Agregar los items del recibo
    items.push_back(new Monto());
    items.push_back(new Antiguedad());
    items.push_back(new EmpleadoACargo());
}

Gestora::~Gestora() {
    for(Empleado* e : empleados) {
        delete e;
    }
    for(Item* i : items) {
        delete i;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Empleado* Gestora::buscarEmpleado(int id) {
    for(Empleado* e : empleados) {
        if(e->getId() == id) {
            return e;
        }
    }
    return nullptr;
}

// ========== EJERCICIO 2: Leer archivo binario ==========

void Gestora::leerArchivo(char* archivo) {
    ifstream archi(archivo, ios::binary);

    if(!archi.is_open()) return;

    EmpleadoArchivo eaux;

    while(archi.read((char*)&eaux, sizeof(EmpleadoArchivo))) {
        Empleado* emp = new Empleado();
        emp->setId(eaux.id);
        emp->setNombre(eaux.nombre);
        emp->setSueldoNeto(eaux.sueldoNeto);
        emp->setAniosAntiguedad(eaux.aniosAntiguedad);
        emp->setEmpleadosACargo(eaux.empleadosACargo);

        empleados.push_back(emp);
    }

    archi.close();
}

// ========== EJERCICIO 3: Guardar recibo en archivo de texto ==========

void Gestora::guardarRecibo(int idEmpleado, char* archivo) {
    Empleado* emp = buscarEmpleado(idEmpleado);

    if(emp == nullptr) return;

    ofstream archi(archivo);

    if(!archi.is_open()) return;

    archi << "=== RECIBO DE SUELDO ===" << endl;
    archi << "ID: " << emp->getId() << endl;
    archi << "Nombre: " << emp->getNombre() << endl;
    archi << "------------------------" << endl;

    double total = 0;

    // Polimorfismo: recorrer todos los items y calcular
    for(Item* item : items) {
        // ========== agregar para punto libre ==========
        // Solo calcular si el empleado tiene asignado este item
        // Si no tiene items asignados (vector vacio), se aplican todos (compatibilidad)
        if(!emp->getTiposItems().empty() && !emp->tieneItem(item->getTipo())) {
            continue;
        }
        double valor = item->calcular(*emp);
        archi << item->getNombreItem() << ": $" << valor << endl;
        total += valor;
    }

    archi << "------------------------" << endl;
    archi << "TOTAL: $" << total << endl;

    archi.close();
}

// ========== EJERCICIO 4: Métodos con STL ==========

// 4a. Empleado con más empleados a cargo
Empleado* Gestora::obtenerEmpleadoMasACargo() {
    if(empleados.empty()) return nullptr;

    auto maxIt = max_element(empleados.begin(), empleados.end(),
        [](Empleado* a, Empleado* b) {
            return a->getEmpleadosACargo() < b->getEmpleadosACargo();
        });

    return *maxIt;
}

// 4b. Monto total que se paga a todos los empleados
double Gestora::obtenerMontoTotalPagado() {
    double total = 0;

    for_each(empleados.begin(), empleados.end(),
        [&total, this](Empleado* emp) {
            for(Item* item : items) {
                // ========== agregar para punto libre ==========
                if(!emp->getTiposItems().empty() && !emp->tieneItem(item->getTipo())) {
                    continue;
                }
                total += item->calcular(*emp);
            }
        });

    return total;
}

// 4c. 5 empleados con más antigüedad ordenados por salario
vector<Empleado*> Gestora::obtener5MasAntiguosPorSalario() {
    if(empleados.empty()) return vector<Empleado*>();

    // 1. Copiar y ordenar por antigüedad (mayor a menor)
    vector<Empleado*> copia(empleados.begin(), empleados.end());

    sort(copia.begin(), copia.end(),
        [](Empleado* a, Empleado* b) {
            return a->getAniosAntiguedad() > b->getAniosAntiguedad();
        });

    // 2. Tomar los primeros 5 (o menos si hay menos de 5)
    int cantidad = min((int)copia.size(), 5);
    vector<Empleado*> top5(copia.begin(), copia.begin() + cantidad);

    // 3. Ordenar esos 5 por salario
    sort(top5.begin(), top5.end(),
        [](Empleado* a, Empleado* b) {
            return a->getSueldoNeto() > b->getSueldoNeto();
        });

    return top5;
}

// ========== agregar para punto libre ==========
// Leer archivo binario que indica qué items aplican a cada empleado
void Gestora::leerArchivoItems(char* archivo) {
    ifstream archi(archivo, ios::binary);

    if(!archi.is_open()) return;

    EmpleadoItemArchivo eiaux;

    while(archi.read((char*)&eiaux, sizeof(EmpleadoItemArchivo))) {
        Empleado* emp = buscarEmpleado(eiaux.idEmpleado);
        if(emp != nullptr) {
            emp->agregarTipoItem(eiaux.tipoItem);
        }
    }

    archi.close();
}

// ========== agregar para punto libre ==========
// Guardar archivo binario con los items asignados a cada empleado
void Gestora::guardarArchivoItems(char* archivo) {
    ofstream archi(archivo, ios::binary);

    if(!archi.is_open()) return;

    EmpleadoItemArchivo eiaux;

    for(Empleado* emp : empleados) {
        vector<char> tipos = emp->getTiposItems();
        for(char tipo : tipos) {
            eiaux.idEmpleado = emp->getId();
            eiaux.tipoItem = tipo;
            archi.write((char*)&eiaux, sizeof(EmpleadoItemArchivo));
        }
    }

    archi.close();
}