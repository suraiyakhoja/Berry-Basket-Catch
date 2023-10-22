#include "../pch.h"
#include "GLFWImplementation.h"


namespace sk
{
	GLFWImplementation::GLFWImplementation()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	void GLFWImplementation::Create(const std::string& name, int width, int height)
	{
		mWindow = glfwCreateWindow(800, 600, "Game_SK", NULL, NULL);

	}
}