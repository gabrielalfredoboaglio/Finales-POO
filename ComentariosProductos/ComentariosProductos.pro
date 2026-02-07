QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = ComentariosProductos

SOURCES += \
        main.cpp \
        comentario.cpp \
        producto.cpp \
        gestora.cpp

HEADERS += \
        comentario.h \
        producto.h \
        gestora.h
