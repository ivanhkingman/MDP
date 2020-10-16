cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

#Project name
project(main)

#Where to find the included source files
include_directories("${PROJECT_SOURCE_DIR}")

#List source related with CPP IMC bindings
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")#file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/src/*.hpp")


#Create static library using all of UDP sources/headers
add_library(src ${HEADERS} ${SOURCES})


add_executable(main main.cpp)
