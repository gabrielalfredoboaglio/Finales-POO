QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = SistemaDependencias

SOURCES += \
        main.cpp \
        paquete.cpp \
        conjuntopaquetes.cpp \
        gestora.cpp

HEADERS += \
        paquete.h \
        conjuntopaquetes.h \
        vectorordenado.h \
        gestora.h
