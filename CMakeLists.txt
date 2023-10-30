cmake_minimum_required(VERSION 3.25)
project(Assembly_Line)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assembly_Line ms1.cpp
        Utilities.cpp
        Utilities.h
        Station.cpp
        Station.h)
