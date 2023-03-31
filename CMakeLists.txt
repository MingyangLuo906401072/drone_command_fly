cmake_minimum_required(VERSION 3.9...3.19)
project(proj3 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

foreach(num RANGE 7)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fpl${num}.txt ${CMAKE_CURRENT_BINARY_DIR}/fpl${num}.txt COPYONLY)
endforeach()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parse_test1.txt ${CMAKE_CURRENT_BINARY_DIR}/parse_test1.txt COPYONLY)

set(SOURCES FlightPlanParse.h FlightPlanParse.cpp Tokens.h Tokens.cpp Opcodes.h Opcodes.cpp IntVariableTable.h IntVariableTable.cpp LabelTable.h LabelTable.cpp InstructionTable.h InstructionTable.cpp DroneCommandTable.h DroneCommandTable.cpp)

add_executable(proj3_main ${SOURCES} proj3_main.cpp)
add_executable(proj3_test catch.hpp ${SOURCES} proj3_test.cpp)

enable_testing()

add_test(proj3_test proj3_test)
