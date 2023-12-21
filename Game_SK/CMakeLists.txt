set(HEADER_FILES	
	Ingredient.h
	Leaf.h
	Power.h
	MyGame.h
)

set(SOURCE_FILES
	main.cpp
	Ingredient.cpp
	Leaf.cpp
	Power.cpp
	MyGame.cpp
)


add_executable(Game_SK ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Game_SK Sky)

include_directories(../Sky/include)