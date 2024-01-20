cmake_minimum_required(VERSION 3.10)
project(EE450_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(EE450_project 
            serverM.cpp
            serverM.h)

target_include_directories(EE450_project PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})