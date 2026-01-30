cmake_minimum_required(VERSION 3.16)

project(ReciboDeSueldo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ReciboDeSueldo main.cpp
    empleado.h empleado.cpp
    item.h item.cpp
    monto.h monto.cpp
    antiguedad.h antiguedad.cpp
    empleadoacargo.h empleadoacargo.cpp
    gestorsistema.h gestorsistema.cpp

)

include(GNUInstallDirs)
install(TARGETS ReciboDeSueldo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
