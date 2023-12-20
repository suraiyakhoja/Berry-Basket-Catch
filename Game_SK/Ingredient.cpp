#include "Ingredient.h"

namespace sk
{
	Ingredient::Ingredient(const std::string& texturePath, int x, int y) : Unit(texturePath, x, y), mTexturePath(texturePath)
	{

	}

	const std::string& Ingredient::GetTexturePath() const {
		return mTexturePath;
	}

	void Ingredient::Fall(int speed) {
		UpdateYCoord(-speed);
	}






}
