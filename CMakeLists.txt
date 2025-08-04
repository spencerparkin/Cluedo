# CMakeLists.txt for the Cluedo project

cmake_minimum_required(VERSION 3.27)

project(Cluedo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CLUEDO_SOURCES
	Source/Main.cpp
	Source/Main.h
	Source/CluedoGame.cpp
	Source/CluedoGame.h
	Source/Player.cpp
	Source/Player.h
	Source/HumanPlayer.cpp
	Source/HumanPlayer.h
	Source/ComputerPlayer.cpp
	Source/ComputerPlayer.h
	Source/Card.cpp
	Source/Card.h
)

source_group("Sources" TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CLUEDO_SOURCES})

add_executable(Cluedo ${CLUEDO_SOURCES})