#pragma once

#include "../Sky/include/Sky.h"

namespace sk
{
	class Leaf : public Unit
	{
	public:
		Leaf(const std::string& image, int x, int y);
		const std::string& GetTexturePath() const;
		void Fall(int speed);
	private:
		std::string mTexturePath;
	};
}