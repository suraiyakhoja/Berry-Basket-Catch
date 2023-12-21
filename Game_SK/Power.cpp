#include "Power.h"
#include "MyGame.h"

sk::Power::Power(const std::string& texturePath, int x, int y) : Unit(texturePath, x, y), mTexturePath(texturePath)

{
}

const std::string& sk::Power::GetTexturePath() const
{
	
	return mTexturePath;
}

void sk::Power::Fall(int speed)
{
	UpdateYCoord(-speed);
}





