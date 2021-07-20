cmake_minimum_required(VERSION 3.5)

project(concordo VERSION 0.1 LANGUAGES CXX )

FILE(GLOB SOURCE_FILES src/*.cpp) #Get all the source files

add_executable(
    concordo
    ${SOURCE_FILES})

#add_definitions(-Wall -g -fsanitize=address -lm) #fsnitize have probles with the code base
add_definitions(-Wall -g -lm)
include_directories(include)
