#include "../Sky/include/Sky.h"
#include "MyGame.h"
#include <iostream>

int main()
{
	MyGame game;

	game.SetKeyPressedCallback([&game](const sk::KeyPressed& e) { game.HandleInput(e); });

	game.Run();

	return 0;
}

//SKY_APPLICATION_START(ColorCollectorGame);

