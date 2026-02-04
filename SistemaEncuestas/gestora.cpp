#include "gestora.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>

Gestora::Gestora() {
}

Gestora::~Gestora() {
    // Liberar memoria de encuestas
    for(Encuesta* e : encuestas) {
        delete e;
    }
}

// ========== MÉTODOS AUXILIARES ==========

Encuesta* Gestora::buscarEncuesta(int indice) {
    if(indice >= 0 && indice < encuestas.size()) {
        return encuestas[indice];
    }
    return nullptr;
}

Pregunta* Gestora::buscarPregunta(int idEncuesta, int idPregunta) {
    Encuesta* enc = buscarEncuesta(idEncuesta);
    if(enc != nullptr) {
        vector<Pregunta*> preguntas = enc->getPreguntas();
        if(idPregunta >= 0 && idPregunta < preguntas.size()) {
            return preguntas[idPregunta];
        }
    }
    return nullptr;
}

Respuesta* Gestora::buscarRespuesta(int idPregunta, int idRespuesta) {
    // Buscar en todas las encuestas
    for(Encuesta* enc : encuestas) {
        vector<Pregunta*> preguntas = enc->getPreguntas();
        for(Pregunta* p : preguntas) {
            if(p == buscarPregunta(0, idPregunta)) {
                vector<Respuesta*> respuestas = p->getRespuestas();
                if(idRespuesta >= 0 && idRespuesta < respuestas.size()) {
                    return respuestas[idRespuesta];
                }
            }
        }
    }
    return nullptr;
}

void Gestora::agregarEncuesta(Encuesta* encuesta) {
    encuestas.push_back(encuesta);
}

vector<Encuesta*> Gestora::getEncuestas() {
    return encuestas;
}

// ========== PUNTO 1: GUARDAR ARCHIVOS BINARIOS ==========

void Gestora::guardarArchivos(char* archEncuestas,
                              char* archPreguntas,
                              char* archRespuestas,
                              char* archPreguntasEncadenadas) {

    // ========== ARCHIVO 1: ENCUESTAS ==========
    ofstream archiE(archEncuestas, ios::binary);

    if(!archiE.is_open()) {
        cout << "Error al crear " << archEncuestas << endl;
        return;
    }

    EncuestaArchivo eaux;

    for(int i = 0; i < encuestas.size(); i++) {
        Encuesta* enc = encuestas[i];
        strcpy(eaux.titulo, enc->getTitulo());
        eaux.cantidadPreguntas = enc->getCantidadPreguntas();

        archiE.write((char*)&eaux, sizeof(EncuestaArchivo));
    }

    archiE.close();

    // ========== ARCHIVO 2: PREGUNTAS ==========
    ofstream archiP(archPreguntas, ios::binary);

    if(!archiP.is_open()) {
        cout << "Error al crear " << archPreguntas << endl;
        return;
    }

    PreguntaArchivo paux;

    for(int i = 0; i < encuestas.size(); i++) {
        Encuesta* enc = encuestas[i];
        vector<Pregunta*> preguntas = enc->getPreguntas();

        for(Pregunta* p : preguntas) {
            strcpy(paux.texto, p->getTexto());
            paux.idEncuesta = i;
            paux.cantidadRespuestas = p->getCantidadRespuestas();

            archiP.write((char*)&paux, sizeof(PreguntaArchivo));
        }
    }

    archiP.close();

    // ========== ARCHIVO 3: RESPUESTAS ==========
    ofstream archiR(archRespuestas, ios::binary);

    if(!archiR.is_open()) {
        cout << "Error al crear " << archRespuestas << endl;
        return;
    }

    RespuestaArchivo raux;
    int idPregunta = 0;

    for(int i = 0; i < encuestas.size(); i++) {
        Encuesta* enc = encuestas[i];
        vector<Pregunta*> preguntas = enc->getPreguntas();

        for(Pregunta* p : preguntas) {
            vector<Respuesta*> respuestas = p->getRespuestas();

            for(Respuesta* r : respuestas) {
                strcpy(raux.texto, r->getTexto());
                raux.idPregunta = idPregunta;
                raux.cantidadPreguntasEncadenadas = r->getCantidadPreguntasEncadenadas();

                archiR.write((char*)&raux, sizeof(RespuestaArchivo));
            }
            idPregunta++;
        }
    }

    archiR.close();

    // ========== ARCHIVO 4: PREGUNTAS_ENCADENADAS ==========
    ofstream archiPE(archPreguntasEncadenadas, ios::binary);

    if(!archiPE.is_open()) {
        cout << "Error al crear " << archPreguntasEncadenadas << endl;
        return;
    }

    PreguntaEncadenadaArchivo peaux;
    idPregunta = 0;
    int idRespuesta = 0;

    for(int i = 0; i < encuestas.size(); i++) {
        Encuesta* enc = encuestas[i];
        vector<Pregunta*> preguntas = enc->getPreguntas();

        for(Pregunta* p : preguntas) {
            vector<Respuesta*> respuestas = p->getRespuestas();

            for(Respuesta* r : respuestas) {
                vector<Pregunta*> preguntasEnc = r->getPreguntasEncadenadas();

                for(Pregunta* pe : preguntasEnc) {
                    peaux.idRespuesta = idRespuesta;
                    // Buscar el ID de la pregunta encadenada
                    int idPreguntaEnc = -1;
                    for(int j = 0; j < encuestas.size(); j++) {
                        Encuesta* enc2 = encuestas[j];
                        vector<Pregunta*> preguntas2 = enc2->getPreguntas();
                        for(int k = 0; k < preguntas2.size(); k++) {
                            if(preguntas2[k] == pe) {
                                idPreguntaEnc = k;
                                break;
                            }
                        }
                    }
                    peaux.idPreguntaEncadenada = idPreguntaEnc;

                    archiPE.write((char*)&peaux, sizeof(PreguntaEncadenadaArchivo));
                }
                idRespuesta++;
            }
            idPregunta++;
        }
    }

    archiPE.close();
}

// ========== LEER ARCHIVOS BINARIOS ==========

void Gestora::leerArchivos(char* archEncuestas,
                           char* archPreguntas,
                           char* archRespuestas,
                           char* archPreguntasEncadenadas) {

    // ========== LEER ENCUESTAS ==========
    ifstream archiE(archEncuestas, ios::binary);

    if(archiE.is_open()) {
        EncuestaArchivo eaux;

        while(archiE.read((char*)&eaux, sizeof(EncuestaArchivo))) {
            Encuesta* enc = new Encuesta(eaux.titulo);
            encuestas.push_back(enc);
        }

        archiE.close();
    }

    // ========== LEER PREGUNTAS ==========
    ifstream archiP(archPreguntas, ios::binary);

    if(archiP.is_open()) {
        PreguntaArchivo paux;

        while(archiP.read((char*)&paux, sizeof(PreguntaArchivo))) {
            Encuesta* enc = buscarEncuesta(paux.idEncuesta);
            if(enc != nullptr) {
                Pregunta* pregunta = new Pregunta(paux.texto);
                enc->agregarPregunta(pregunta);
            }
        }

        archiP.close();
    }

    // ========== LEER RESPUESTAS ==========
    ifstream archiR(archRespuestas, ios::binary);

    if(archiR.is_open()) {
        RespuestaArchivo raux;
        map<int, vector<Respuesta*>> respuestasPorPregunta;
        int idPregunta = 0;

        while(archiR.read((char*)&raux, sizeof(RespuestaArchivo))) {
            Respuesta* respuesta = new Respuesta(raux.texto);
            respuestasPorPregunta[idPregunta].push_back(respuesta);
            idPregunta++;
        }

        // Asignar respuestas a preguntas
        int preguntaActual = 0;
        for(Encuesta* enc : encuestas) {
            vector<Pregunta*> preguntas = enc->getPreguntas();
            for(Pregunta* p : preguntas) {
                if(respuestasPorPregunta.find(preguntaActual) != respuestasPorPregunta.end()) {
                    for(Respuesta* r : respuestasPorPregunta[preguntaActual]) {
                        p->agregarRespuesta(r);
                    }
                }
                preguntaActual++;
            }
        }

        archiR.close();
    }

    // ========== LEER PREGUNTAS_ENCADENADAS ==========
    ifstream archiPE(archPreguntasEncadenadas, ios::binary);

    if(archiPE.is_open()) {
        PreguntaEncadenadaArchivo peaux;
        int idRespuesta = 0;

        while(archiPE.read((char*)&peaux, sizeof(PreguntaEncadenadaArchivo))) {
            Respuesta* respuesta = buscarRespuesta(0, peaux.idRespuesta);
            Pregunta* preguntaEnc = buscarPregunta(0, peaux.idPreguntaEncadenada);

            if(respuesta != nullptr && preguntaEnc != nullptr) {
                respuesta->agregarPreguntaEncadenada(preguntaEnc);
            }
            idRespuesta++;
        }

        archiPE.close();
    }
}

// ========== PUNTO 2: PROCEDIMIENTO PARA RESPONDER ENCUESTA ==========

void Gestora::responderEncuesta(int indiceEncuesta) {
    Encuesta* enc = buscarEncuesta(indiceEncuesta);

    if(enc == nullptr) {
        cout << "Encuesta no encontrada" << endl;
        return;
    }

    responderPreguntas(enc->getPreguntas());
}

void Gestora::responderPreguntas(vector<Pregunta*> preguntas) {
    for(Pregunta* p : preguntas) {
        cout << p->getTexto() << endl;
        
        vector<Respuesta*> respuestas = p->getRespuestas();
        for(int i = 0; i < respuestas.size(); i++) {
            cout << (i + 1) << ". " << respuestas[i]->getTexto() << endl;
        }
        
        int opcion;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        
        if(opcion >= 1 && opcion <= respuestas.size()) {
            Respuesta* respuestaSeleccionada = respuestas[opcion - 1];
            
            // Si la respuesta tiene preguntas encadenadas, responderlas
            if(respuestaSeleccionada->tienePreguntasEncadenadas()) {
                responderPreguntas(respuestaSeleccionada->getPreguntasEncadenadas());
            }
        }
    }
}

// ========== PUNTO 3: MÉTODOS CON STL ==========

vector<Pregunta*> Gestora::obtenerPreguntasConMasRespuestas() {
    if(encuestas.empty()) {
        return vector<Pregunta*>();
    }

    vector<Pregunta*> todasLasPreguntas;

    // Recolectar todas las preguntas de todas las encuestas
    for(Encuesta* enc : encuestas) {
        vector<Pregunta*> preguntas = enc->getPreguntas();
        todasLasPreguntas.insert(todasLasPreguntas.end(), preguntas.begin(), preguntas.end());
    }

    if(todasLasPreguntas.empty()) {
        return vector<Pregunta*>();
    }

    // Encontrar el máximo usando STL
    auto maxIt = max_element(todasLasPreguntas.begin(), todasLasPreguntas.end(),
                             [](Pregunta* a, Pregunta* b) {
                                 return a->getCantidadRespuestas() < b->getCantidadRespuestas();
                             });

    int maxRespuestas = (*maxIt)->getCantidadRespuestas();

    // Recolectar todas las que tienen ese máximo
    vector<Pregunta*> resultado;

    for(Pregunta* p : todasLasPreguntas) {
        if(p->getCantidadRespuestas() == maxRespuestas) {
            resultado.push_back(p);
        }
    }

    return resultado;
}

vector<Respuesta*> Gestora::obtenerRespuestasConPreguntasEncadenadas() {
    vector<Respuesta*> resultado;

    // Recorrer todas las encuestas, preguntas y respuestas
    for(Encuesta* enc : encuestas) {
        vector<Pregunta*> preguntas = enc->getPreguntas();

        for(Pregunta* p : preguntas) {
            vector<Respuesta*> respuestas = p->getRespuestas();

            for(Respuesta* r : respuestas) {
                if(r->tienePreguntasEncadenadas()) {
                    resultado.push_back(r);
                }
            }
        }
    }

    return resultado;
}

// ========== LIBRE: GUARDAR EN TEXTO ==========

void Gestora::guardarEnTexto(char* archivoTexto) {
    ofstream archivo(archivoTexto);

    if(!archivo.is_open()) {
        cout << "Error al crear " << archivoTexto << endl;
        return;
    }

    for(Encuesta* enc : encuestas) {
        archivo << *enc;
    }

    archivo.close();
}
