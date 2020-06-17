cmake_minimum_required(VERSION 3.16)
project(boundvar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Ofast")

add_executable(boundvar main.cpp UM.cpp UM.h)