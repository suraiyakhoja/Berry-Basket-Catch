#pragma once

#include "../WindowImplementation.h"
#include "GLFW/glfw3.h"
namespace sk
{
	class GLFWImplementation : public WindowImplementation
	{
	public: 
		GLFWImplementation();
		void Create(const std::string& name, int width, int height) override;
		int GetHeight() const override;
		int GetWidth() const override;
		virtual void SwapBuffers() override;
		virtual void PollEvents() override;

	private:
		GLFWwindow* mWindow;

	};
}