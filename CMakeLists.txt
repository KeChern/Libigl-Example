cmake_minimum_required(VERSION 3.5)
project(example)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)

igl_include(glfw)
#igl_include(embree)
igl_include(imgui)
#igl_include(opengl)
#igl_include(stb)
#igl_include(predicates)
#igl_include(xml)
#igl_include(copyleft cgal)
#igl_include(copyleft comiso)
#igl_include(copyleft core)
#igl_include(copyleft cork)
#igl_include(copyleft tetgen)
#igl_include(restricted matlab)
#igl_include(restricted mosek)
#igl_include(restricted triangle)

#########################################
#####                               #####
#####             Core              #####
#####                               #####
#########################################
file(GLOB CoreFiles
        src/Mesh/*.h
        src/Mesh/*.cpp
        src/Utility/*.h
        src/Utility/*.cpp)
add_library(CoreLib STATIC ${CoreFiles})
target_include_directories(CoreLib PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(CoreLib PUBLIC igl::glfw)

#########################################
#####                               #####
#####           Interface           #####
#####                               #####
#########################################
file(GLOB InterfaceFiles
        src/Interface/*.h
        src/Interface/*.cpp)
add_library(InterfaceLib STATIC ${InterfaceFiles})
target_link_libraries(InterfaceLib PUBLIC igl::imgui)

#########################################
#####                               #####
#####        Executable File        #####
#####                               #####
#########################################
add_executable(${PROJECT_NAME} src/MainFunc/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PUBLIC
        # ours
        CoreLib
        InterfaceLib

        # igl
        igl::glfw
        # igl::embree
        igl::imgui
        # igl::opengl
        # igl::stb
        # igl::predicates
        # igl::xml
        # igl_copyleft::cgal
        # igl_copyleft::comiso
        # igl_copyleft::core
        # igl_copyleft::cork
        # igl_copyleft::tetgen
        # igl_restricted::matlab
        # igl_restricted::mosek
        # igl_restricted::triangle
)
