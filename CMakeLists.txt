cmake_minimum_required(VERSION 3.17)
project(Proyecto_1_Datos_2)

set(CMAKE_CXX_STANDARD 20)

#gtkmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
#---
add_executable(Proyecto_1_Datos_2 main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})
