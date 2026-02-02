QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = SistemaArchivosMemoria
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        nodo.cpp \
        archivo.cpp \
        carpeta.cpp \
        gestora.cpp

HEADERS += \
        nodo.h \
        archivo.h \
        carpeta.h \
        gestora.h
