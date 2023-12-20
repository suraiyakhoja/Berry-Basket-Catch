#pragma once


#include "Utilities.h"

namespace sk
{
	class SKY_API KeyPressed
	{
	public:
		KeyPressed(int kCode);

		int GetKeyCode() const;

	private:
		int mKeyCode;
	};

	class SKY_API KeyReleased
	{
	public:
		KeyReleased(int kCode);

		int GetKeyCode() const;

	private:
		int mKeyCode;
	};

	class SKY_API WindowClosed
	{

	};
}