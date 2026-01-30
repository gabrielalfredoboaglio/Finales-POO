cmake_minimum_required(VERSION 3.16)

project(SistemaDescuento-Herencia-Composicion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SistemaDescuento-Herencia-Composicion main.cpp

    descuento.h descuento.cpp
    descuentoa.h descuentoa.cpp
    descuentob.h descuentob.cpp
    descuentoc.h descuentoc.cpp
    gestora.h gestora.cpp
    venta.h venta.cpp
    cliente.h cliente.cpp)

include(GNUInstallDirs)
install(TARGETS SistemaDescuento-Herencia-Composicion
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
