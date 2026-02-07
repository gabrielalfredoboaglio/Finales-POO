#ifndef GESTORA_H
#define GESTORA_H

#include "nodo.h"
#include "archivo.h"
#include "carpeta.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Gestora {
private:
    Carpeta* root;
    Carpeta* carpetaActual;

    // Métodos auxiliares privados
    string construirPath(string nombre);
    bool validarPathUnico(string path);
    Carpeta* buscarCarpetaPorPath(string path);

public:
    Gestora();
    ~Gestora();

    // Comandos del sistema
    bool mkdir(string nombre);
    bool touch(string nombre, int peso);
    bool cd(string nombre);
    void ls();
    void lsp();
    void pwd();

    // Getters
    Carpeta* getRoot();
    Carpeta* getCarpetaActual();
};

#endif // GESTORA_H
