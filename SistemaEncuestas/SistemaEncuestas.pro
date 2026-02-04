QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = SistemaEncuestas
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        respuesta.cpp \
        pregunta.cpp \
        encuesta.cpp \
        gestora.cpp

HEADERS += \
        respuesta.h \
        pregunta.h \
        encuesta.h \
        gestora.h
