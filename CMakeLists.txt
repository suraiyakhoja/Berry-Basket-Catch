cmake_minimum_required(VERSION 3.24)

project(Game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(WIN32)
	add_definitions(-DSKY_MSCPP)
elseif(LINUX)
	add_definitions(-DSKY_LINUX)
elseif(APPLE)
	add_definitions(-DSKY_APPLE)
endif()

add_subdirectory(glfw)
add_subdirectory(Sky)
add_subdirectory(Game_SK)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Game_SK)