#pragma once

#include "pch.h"
#include "Utilities.h"
#include "WindowImplementation.h"
namespace sk
{
	class SKY_API GameWindow
	{
	public:
		GameWindow();
		void Create(const std::string& name, int width, int height);
		int GetHeight() const;
		int GetWidth() const;
		void SwapBuffers();
		void PollEvents();
	private:
		std::unique_ptr<WindowImplementation> mImplementation{ nullptr };

	};
}