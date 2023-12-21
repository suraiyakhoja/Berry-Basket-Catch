#pragma once

#include "../Sky/include/Sky.h"
//#include "SkyApp.h"
//#include "Picture.h"
//#include "Events.h"
//#include "Unit.h"
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

	const sk::Unit& GetPlayer() const { return mBasket; }
	sk::Unit& GetPlayer() { return mBasket; }

	void AddFallingFruit();
	void AddFallingLeaf();

	void DrawScore(int x, int y, int score);
	std::vector<sk::Picture> LoadDigitTextures();

	void AddFallingPower();
	void IncreaseSpeed();
	void UpdatePower();

	bool IsOverlappingExistingObjects(int x, int y, int objectSize);



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
	int mBasketSpeed = 30;
	std::chrono::time_point<std::chrono::steady_clock> mPowerStartTime;

	std::vector<sk::Leaf> mLeaves;
	int mLeavesCaught = 0;
	int mLeafSpawnInterval = 25;

	std::vector<sk::Power> mPower;


	void CheckFruitCollision();
	void CheckLeafCollision();
	void CheckPowerCollision();
	void UpdateScore();

//	static constexpr int FruitFallSpeed = 5;
	int InitialFruitSpawnInterval = 24;
	static constexpr int FruitSize = 5;

	static constexpr int LeafSize = 5;

	static constexpr int PowerSize = 5;

	std::chrono::time_point<std::chrono::steady_clock> mStartTime;
	std::chrono::time_point<std::chrono::steady_clock> mCurrentTime;
};

