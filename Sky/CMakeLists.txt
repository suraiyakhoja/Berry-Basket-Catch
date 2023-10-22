set(HEADER_FILES
	include/Sky.h
	SkyApp.h
	Utilities.h
)

set(SOURCE_FILES
	placeholder.cpp
)

add_definitions(-DSK_DEBUG=2)
add_definitions(-DSKY_LIB)

if(WIN32)
	add_definitions(-DSKY_MSCPP)
elseif(LINUX)
	add_definitions(-DSKY_LINUX)
elseif(APPLE)
	add_definitions(-DSKY_APPLE)
endif()


add_library(Sky SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_precompile_headers(Sky PRIVATE pch.h)
