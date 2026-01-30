cmake_minimum_required(VERSION 3.16)

project(Bonos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Bonos main.cpp
    empleado.h empleado.cpp
    jefe.h jefe.cpp
    vendedor.h vendedor.cpp
    gestora.h gestora.cpp
    empleadomuchasventas.h empleadomuchasventas.cpp


)

include(GNUInstallDirs)
install(TARGETS Bonos
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
