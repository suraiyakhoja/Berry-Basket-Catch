set(HEADER_FILES
	
)

set(SOURCE_FILES
	main.cpp
)


add_executable(Game_SK ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Game_SK Sky)

include_directories(../Sky/include)