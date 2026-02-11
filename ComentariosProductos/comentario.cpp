#include "comentario.h"
#include <cstring>

using namespace std;

Comentario::Comentario() {
    id = 0;
    strcpy(texto, "");
    puntaje = 0;
}

Comentario::Comentario(char* txt, int punt) {
    id = 0;
    strcpy(texto, txt);
    puntaje = punt;
}

Comentario::~Comentario() {
    for(Comentario* hijo : comentariosHijos) {
        delete hijo;
    }
}

char* Comentario::getTexto() {
    return texto;
}

int Comentario::getPuntaje() {
    return puntaje;
}

vector<Comentario*> Comentario::getComentariosHijos() {
    return comentariosHijos;
}

int Comentario::getCantidadComentariosHijos() {
    return comentariosHijos.size();
}

void Comentario::setTexto(char* txt) {
    strcpy(texto, txt);
}

void Comentario::setPuntaje(int punt) {
    puntaje = punt;
}

void Comentario::agregarComentarioHijo(Comentario* comentario) {
    comentariosHijos.push_back(comentario);
}

double Comentario::calcularPuntajePromedio() {
    int suma = puntaje;
    int cantidad = 1;

    for(Comentario* hijo : comentariosHijos) {
        double promHijo = hijo->calcularPuntajePromedio();
        suma += promHijo;
        cantidad++;
    }

    if(cantidad == 0) return 0;
    return (double)suma / cantidad;
}

int Comentario::contarComentariosTotales() {
    int total = 1;

    for(Comentario* hijo : comentariosHijos) {
        total += hijo->contarComentariosTotales();
    }

    return total;
}

int Comentario::contarComentariosNegativos() {
    int negativos = (puntaje < 2) ? 1 : 0;

    for(Comentario* hijo : comentariosHijos) {
        negativos += hijo->contarComentariosNegativos();
    }

    return negativos;
}

void Comentario::obtenerTodosComentarios(vector<Comentario*>& resultado) {
    resultado.push_back(this);

    for(Comentario* hijo : comentariosHijos) {
        hijo->obtenerTodosComentarios(resultado);
    }
}

// ========== agregar para punto libre ==========
int Comentario::getId() { return id; }
void Comentario::setId(int i) { id = i; }

void Comentario::agregarPadre(Comentario* padre) {
    comentariosPadres.push_back(padre);
    // También agregar como hijo del padre si no lo tiene
    vector<Comentario*> hijos = padre->getComentariosHijos();
    bool yaEsHijo = false;
    for(Comentario* h : hijos) {
        if(h->getId() == this->id) {
            yaEsHijo = true;
            break;
        }
    }
    if(!yaEsHijo) {
        padre->agregarComentarioHijo(this);
    }
}

vector<Comentario*> Comentario::getPadres() {
    return comentariosPadres;
}

int Comentario::getCantidadPadres() {
    return comentariosPadres.size();
}
