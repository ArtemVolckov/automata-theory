cmake_minimum_required(VERSION 3.16)

project(TA_lab2)

set (CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/regex ${CMAKE_SOURCE_DIR}/ast ${CMAKE_SOURCE_DIR}/nfa_dfa ${CMAKE_SOURCE_DIR}/test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCES test/catch2.cpp regex/regex.cpp ast/ast.cpp nfa_dfa/nfa_dfa.cpp)

find_package(Catch2 3 REQUIRED)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE Catch2::Catch2WithMain)
