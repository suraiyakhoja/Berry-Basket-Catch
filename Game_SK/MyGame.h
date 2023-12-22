#pragma once

#include "../Sky/include/Sky.h"
#include "Ingredient.h"
#include "Leaf.h"
#include "Power.h"
#include <random>

class MyGame : public sk::SkyApp<MyGame>
{
public:
	MyGame();
	void OnUpdate() override;
	void HandleInput(const sk::KeyPressed& keyPressedEvent);

	const sk::Unit& GetBasket() const { return mBasket; }
	sk::Unit& GetBasket() { return mBasket; }

	void AddFallingFruit();
	void AddFallingLeaf();
	void AddFallingPower();
	void IncreaseSpeed();
	void UpdatePower();

	void CheckFruitCollision();
	void CheckLeafCollision();
	void CheckPowerCollision();

	std::vector<sk::Picture> LoadDigitTextures();
	void DrawScore(int x, int y, int score);

	bool IsOverlappingExistingObjects(int x, int y, int objectSize);

	int RandomInt(int min, int max);




private:
	int mFrameCount;
	int mScore;
	int mFallSpeed;
	int mFruitsCaught;
	int mFallingFruits;
	int mBasketSpeed = 30;

	sk::Picture mBasketTexture;
	sk::Unit mBasket;

	std::vector<sk::Ingredient> mFruits;

	std::vector<sk::Leaf> mLeaves;
	int mLeavesCaught = 0;
	int mLeafSpawnInterval = 25;

	int InitialFruitSpawnInterval = 24;

	std::vector<sk::Power> mPower;

	int mFruitSize = 5;
	int mLeafSize = 5;
	int mPowerSize = 5;

	std::chrono::time_point<std::chrono::steady_clock> mPowerStartTime;
	std::chrono::time_point<std::chrono::steady_clock> mStartTime;
	std::chrono::time_point<std::chrono::steady_clock> mCurrentTime;

};

