TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    cliente.cpp \
    clientebasico.cpp \
    clientemedio.cpp \
    clientepremium.cpp \
    gestora.cpp

HEADERS += \
    cliente.h \
    clientebasico.h \
    clientemedio.h \
    clientepremium.h \
    gestora.h
