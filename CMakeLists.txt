cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

#Project name
project(MDP)

#Where to find the included source files
include_directories(include)

#Create static library for transition class
file(GLOB_RECURSE TRANSITION_SOURCES "${PROJECT_SOURCE_DIR}/source/transition.cpp")
file(GLOB_RECURSE TRANSITION_HEADERS "${PROJECT_SOURCE_DIR}/include/transition.hpp")
add_library(transition ${TRANSITION_HEADERS} ${TRANSITION_SOURCES})

#Create static library for dynamic message passing
file(GLOB_RECURSE DMP_HEADERS "${PROJECT_SOURCE_DIR}/include/dmp.hpp")
file(GLOB_RECURSE DMP_SOURCES "${PROJECT_SOURCE_DIR}/include/dmp.cpp")
add_library(dmp ${DMP_HEADERS} ${TRANSITION_SOURCES})

#Add sources
file(GLOB SOURCES "source/*.cpp")

add_executable(mdp ${SOURCES})
