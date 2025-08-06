# CMakeLists.txt for the Cluedo project

set(CLUEDO_SOURCES
	Source/Application.cpp
	Source/Application.h
	Source/Frame.cpp
	Source/Frame.h
	Source/Canvas.cpp
	Source/Canvas.h
	Source/Player.cpp
	Source/Player.h
	Source/HumanPlayer.cpp
	Source/HumanPlayer.h
	Source/ComputerPlayer.cpp
	Source/ComputerPlayer.h
	Source/Game.cpp
	Source/Game.h
	Source/Card.cpp
	Source/Card.h
)

source_group("Sources" TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CLUEDO_SOURCES})

add_executable(Cluedo WIN32
	${CLUEDO_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/wx_dpi_aware_pmv2.manifest
)

target_compile_definitions(Cluedo PUBLIC
	__WXMSW__
	_UNICODE
)

target_compile_definitions(Cluedo PRIVATE
	WIN32_LEAN_AND_MEAN
	NOMINMAX
	_USE_MATH_DEFINES
)

target_link_libraries(ClueGameClient
	wx::core
	wx::base
	wx::net
	wx::gl
)