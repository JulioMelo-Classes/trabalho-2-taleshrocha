cmake_minimum_required(VERSION 3.5)

project(concordo VERSION 0.1 LANGUAGES CXX )

FILE(GLOB SOURCE_FILES src/*.cpp) #Get all the source files

add_executable(
    concordo
    ${SOURCE_FILES})

#add_definitions(-Wall -g -fsanitize=address -lm) #fsnitize have probles with the code base
#é ruim usar esse tipo de linha no cmakelist pois é não portável. se vc quiser forçar o padrão do C++ use set_property(TARGET tgt PROPERTY CXX_STANDARD 11)
add_definitions(-Wall -g -std=c++2a -lm)
include_directories(include)
