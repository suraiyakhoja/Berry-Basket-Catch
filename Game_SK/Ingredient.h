#pragma once

//#include "Unit.h"
#include "../Sky/include/Sky.h"

namespace sk
{
	class Ingredient : public Unit
	{
	public:
		Ingredient(const std::string& image, int x, int y);
		const std::string& GetTexturePath() const;

		void Fall(int speed);

		//int GetXCoord() const;
		//int GetYCoord() const;


	private:
		//int mXCoord;
		//int mYCoord;
		std::string mTexturePath;
	};
}
