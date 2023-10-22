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

include_directories(../glfw/include)


add_library(Sky SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_precompile_headers(Sky PRIVATE pch.h)

target_link_libraries(Sky glfw)
