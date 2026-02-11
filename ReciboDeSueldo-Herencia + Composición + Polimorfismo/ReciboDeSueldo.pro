TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    empleado.cpp \
    item.cpp \
    monto.cpp \
    antiguedad.cpp \
    empleadoacargo.cpp \
    gestora.cpp

HEADERS += \
    empleado.h \
    item.h \
    monto.h \
    antiguedad.h \
    empleadoacargo.h \
    gestora.h
