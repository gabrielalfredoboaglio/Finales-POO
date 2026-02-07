QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = EmpresaProductosAlimenticios
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        ingrediente.cpp \
        producto.cpp \
        productocompuesto.cpp \
        gestora.cpp

HEADERS += \
        ingrediente.h \
        producto.h \
        productocompuesto.h \
        gestora.h
