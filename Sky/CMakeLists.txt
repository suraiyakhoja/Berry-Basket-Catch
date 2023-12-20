set(HEADER_FILES
	include/Sky.h
	SkyApp.h
	Utilities.h
	GameWindow.h
	WindowImplementation.h
	GLFWCode/GLFWImplementation.h
	GLFWCode/OpenGLPicture.h
	GLFWCode/OpenGLRenderer.h
	GLFWCode/OpenGLShader.h
	Picture.h
	PictureImplementation.h
	Renderer.h
	RendererImplementation.h
	Shader.h
	ShaderImplementation.h
	Unit.h
	Utilities.h
	WindowImplementation.h
	Keys.h
)

set(SOURCE_FILES
	GameWindow.cpp
	GLFWCode/GLFWImplementation.cpp
	GLFWCode/OpenGLPicture.cpp
	GLFWCode/OpenGLRenderer.cpp
	GLFWCode/OpenGLShader.cpp
	Picture.cpp
	Renderer.cpp
	Shader.cpp
	Unit.cpp
)

add_definitions(-DSK_DEBUG=2)
add_definitions(-DSKY_LIB)

include_directories(../Sky)
include_directories(../glfw/include)
include_directories(../glad/include)
include_directories(../stbi)



add_library(Sky SHARED ${HEADER_FILES} ${SOURCE_FILES})

target_precompile_headers(Sky PRIVATE pch.h)

target_link_libraries(Sky glfw)
target_link_libraries(Sky glad)
target_link_libraries(Sky stbi)
