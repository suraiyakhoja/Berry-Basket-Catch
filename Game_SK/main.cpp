#include "Sky.h"
#include <iostream>

class MyGame : public sk::SkyApp<MyGame>
{
public:
	virtual void OnUpdate() override
	{
		std::cout << "Sky running" << std::endl;
	}
};

SKY_APPLICATION_START(MyGame);

