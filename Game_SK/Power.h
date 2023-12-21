#pragma once

#include "../Sky/include/Sky.h"
//#include "MyGame.h"
namespace sk
{
	class MyGame;
	class Power : public Unit
	{
	public:
		Power(const std::string& image, int x, int y);
		const std::string& GetTexturePath() const;
		void Fall(int speed);

	private:
		std::string mTexturePath;




	};
}