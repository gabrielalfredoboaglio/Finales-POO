cmake_minimum_required(VERSION 3.16)

project(AutorizacionesEmpresa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AutorizacionesEmpresa main.cpp
    usuario.h usuario.cpp
    cargo.h cargo.cpp
    gestora.h gestora.cpp
    cargoextendido.h cargoextendido.cpp)

include(GNUInstallDirs)
install(TARGETS AutorizacionesEmpresa
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
