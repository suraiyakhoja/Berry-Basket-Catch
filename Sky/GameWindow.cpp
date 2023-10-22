#include "pch.h"
#include "GameWindow.h"

namespace sk
{
	void GameWindow::Create(const std::string& name, int width, int height)
	{
		mImplementation->Create(name, width, height);
	}
	int GameWindow::GetHeight() const
	{
		return mImplementation->GetHeight();
	}
	int GameWindow::GetWidth() const
	{
		return mImplementation->GetWidth();
	}
}