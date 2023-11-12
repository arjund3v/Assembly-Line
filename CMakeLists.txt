cmake_minimum_required(VERSION 3.25)
project(Assembly_Line)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assembly_Line ms3.cpp
        Utilities.cpp
        Utilities.h
        Station.cpp
        Station.h
        CustomerOrder.cpp
        CustomerOrder.h
        Workstation.cpp
        Workstation.h
        LineManager.cpp
        LineManager.h)
