#include "Leaf.h"

sk::Leaf::Leaf(const std::string& texturePath, int x, int y) : Unit(texturePath, x, y), mTexturePath(texturePath)
{
}

const std::string& sk::Leaf::GetTexturePath() const
{
	return mTexturePath;
}


void sk::Leaf::Fall(int speed)
{
	UpdateYCoord(-speed);
}
