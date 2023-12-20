set(HEADER_FILES	
	Ingredient.h
	MyGame.h
)

set(SOURCE_FILES
	main.cpp
	Ingredient.cpp
	MyGame.cpp
)


add_executable(Game_SK ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Game_SK Sky)

include_directories(../Sky/include)