cmake_minimum_required(VERSION 3.5)

project(concordo VERSION 0.1 LANGUAGES CXX )

FILE(GLOB SOURCE_FILES src/*.cpp) #Get all the source files

include_directories(include)
add_executable(
    concordo
    ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-Wall -g -fsanitize=address -std=c++2a -lm")
