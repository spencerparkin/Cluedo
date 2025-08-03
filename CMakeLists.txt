# CMakeLists.txt for the CluedoSim project

cmake_minimum_required(VERSION 3.27)

project(CluedoSim)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLUEDO_SIM_SOURCES
	Source/Main.cpp
	Source/Main.h
)

source_group("Sources" TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CLUEDO_SIM_SOURCES})

add_executable(CluedoSim ${CLUEDO_SIM_SOURCES})