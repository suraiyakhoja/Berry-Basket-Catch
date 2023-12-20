#pragma once

#include "../Sky/include/Sky.h"
//#include "SkyApp.h"
//#include "Picture.h"
//#include "Events.h"
//#include "Unit.h"
#include "Ingredient.h"
#include <random>

class MyGame : public sk::SkyApp<MyGame>
{
public:
	MyGame();
	void OnUpdate() override;
	void HandleInput(const sk::KeyPressed& keyPressedEvent);

	const sk::Unit& GetPlayer() const { return mBasket; }
	sk::Unit& GetPlayer() { return mBasket; }

	void AddFallingFruit();

	void DrawScore(int x, int y, int score);
	std::vector<sk::Picture> LoadDigitTextures();

private:
	int RandomInt(int min, int max);
	int mFrameCount;

	sk::Picture mBasketTexture;
	sk::Unit mBasket;

	//sk::Picture mAppleTexture;
	///sk::Unit mApple;

	std::vector<sk::Ingredient> mFruits;

	int mScore;
	int mFallSpeed;
	int mFruitsCaught;
	int mFallingFruits;

	void CheckCollision();
	void UpdateScore();

//	static constexpr int FruitFallSpeed = 5;
	int InitialFruitSpawnInterval = 30;
	static constexpr int FruitSize = 5;
};

