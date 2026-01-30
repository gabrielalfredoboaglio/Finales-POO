cmake_minimum_required(VERSION 3.16)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled main.cpp

    repetitiva.h repetitiva.cpp
    normal.h normal.cpp
    archivotxt.h archivotxt.cpp
    gestora.h gestora.cpp
    tarea.h tarea.cpp
    muchatarea.h muchatarea.cpp
    gestorasinejerciciolibre.h gestorasinejerciciolibre.cpp
)

include(GNUInstallDirs)
install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
