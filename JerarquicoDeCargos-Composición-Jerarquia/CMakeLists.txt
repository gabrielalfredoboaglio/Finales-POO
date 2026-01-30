cmake_minimum_required(VERSION 3.16)

project(JerarquicoDeCargos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(JerarquicoDeCargos main.cpp
    empleado.h empleado.cpp
    gestora.h gestora.cpp)

include(GNUInstallDirs)
install(TARGETS JerarquicoDeCargos
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
