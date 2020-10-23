cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

#Project name
project(MDP)

#Where to find the included source files
include_directories(include)

#Add sources
file(GLOB SOURCES "source/*.cpp")

add_executable(mdp ${SOURCES})
