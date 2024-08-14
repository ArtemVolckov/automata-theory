cmake_minimum_required(VERSION 3.16)

project(TA_lab2)

set (CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/regex ${CMAKE_SOURCE_DIR}/ast)

set(SOURCES main.cpp regex/regex.cpp ast/ast.cpp)

add_executable(main ${SOURCES})
