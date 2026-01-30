#include "gestora.h"
#include "normal.h"
#include "archivotxt.h"
#include "repetitiva.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <string>
#include <cstring>

using namespace std;

Gestora::Gestora() {}

Gestora::~Gestora() {
    // Liberar memoria de todas las tareas
    for (Tarea* t : tareas) {
        delete t;
    }
}

void Gestora::add(Tarea* t) {
    tareas.push_back(t);
}

void Gestora::leer() {
    std::ifstream archi("data.dat", std::ios::binary);
    TareaArchivo str;
    Tarea* tarea = nullptr;

    if (!archi.is_open()) return;

    while (archi.read((char*)&str, sizeof(TareaArchivo))) {
        switch (str.tipo) {
        case 'N':
            tarea = new Normal();
            break;
        case 'A':
            tarea = new ArchivoTxt();
            break;
        case 'R':
            tarea = new Repetitiva(this);
            break;
        default:
            continue;
        }

        tarea->setStr(str);
        this->tareas.push_back(tarea);
    }
    archi.close();
}

void Gestora::guardar() {
    std::ofstream archi("data.dat", std::ios::binary);
    if (!archi.is_open()) return;

    for (Tarea* t : tareas) {
        TareaArchivo str = t->getStr();
        archi.write((char*)&str, sizeof(TareaArchivo));
    }
    archi.close();
}

std::vector<Tarea*> Gestora::mayor() {
    if (tareas.empty()) return {};

    std::vector<Tarea*> resultado;
    std::sort(this->tareas.begin(), this->tareas.end(),
              [](Tarea* a, Tarea* b) -> bool {
                  return a->getDuracion() > b->getDuracion();
              });

    int maxDuracion = this->tareas.front()->getDuracion();

    for (auto tarea : this->tareas) {
        if (tarea->getDuracion() == maxDuracion) {
            resultado.push_back(tarea);
        } else {
            break;
        }
    }
    return resultado;
}

std::string Gestora::dia() {
    if (tareas.empty()) return "";

    std::map<std::string, int> map;
    for (auto tarea : this->tareas) {
        std::string dia(tarea->getFecha());
        map[dia]++;
    }

    std::string maxDia;
    int max = 0;
    for (auto p : map) {
        if (p.second > max) {
            max = p.second;
            maxDia = p.first;
        }
    }
    return maxDia;
}

std::vector<std::pair<Tarea*, Tarea*>> Gestora::obtenerTareasSuperpuestas() {
    // Generar pares
    std::vector<std::pair<Tarea*, Tarea*>> pares;
    for (size_t i = 0; i < tareas.size(); i++)
        for (size_t j = i + 1; j < tareas.size(); j++)
            pares.push_back({tareas[i], tareas[j]});

    // Filtrar con accumulate
    return std::accumulate(pares.begin(), pares.end(),
                           std::vector<std::pair<Tarea*, Tarea*>>(),
                           [](auto res, auto par) {
                               if (strcmp(par.first->getFecha(), par.second->getFecha()) != 0)
                                   return res;

                               auto hm = [](const char* h) {
                                   std::string s(h);
                                   return std::stoi(s.substr(0,2))*60 + std::stoi(s.substr(2,2));
                               };

                               int i1 = hm(par.first->getHora());
                               int f1 = i1 + par.first->getDuracion();
                               int i2 = hm(par.second->getHora());
                               int f2 = i2 + par.second->getDuracion();

                               if (i1 < f2 && i2 < f1)
                                   res.push_back(par);

                               return res;
                           });
}
