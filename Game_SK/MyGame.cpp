#include "MyGame.h"

MyGame::MyGame() :
	mBasket("../Assets/Pictures/basket.png", 0, 0), mBasketTexture("../Assets/Pictures/basket.png"),
	mFrameCount(0), mFallSpeed(10), mFruitsCaught(0), mScore(0), mFallingFruits(1)
{
}

void MyGame::OnUpdate()
{
	mRenderer.Clear();
	sk::Picture backgroundPicture("../Assets/Pictures/background.png");
	mRenderer.Draw(0, 0, backgroundPicture);

	mRenderer.Draw(mBasket.GetXCoord(), mBasket.GetYCoord(), mBasketTexture);


	if (mFrameCount % (InitialFruitSpawnInterval / mFallingFruits) == 0) {
		AddFallingFruit();
	}
	
	if (mFruitsCaught >= 5 && mFrameCount % mLeafSpawnInterval == 0)
	{
		AddFallingLeaf();
	}

	if (mFruitsCaught >= 10 && mFrameCount % 20 == 0)
	{
		if (mFruitsCaught % 5 == 0)
		{
			AddFallingPower();
		}
	}
	
	
	for (auto& fruit : mFruits) 
	{
		fruit.Fall(mFallSpeed);
		std::string fruitTexturePath = fruit.GetTexturePath();
		sk::Picture fruitPicture(fruitTexturePath); // Convert the path to a Picture
		mRenderer.Draw(fruit.GetXCoord(), fruit.GetYCoord(), fruitPicture);
	}
	
	for (auto& leaf : mLeaves) 
	{
		leaf.Fall(mFallSpeed);
		std::string leafTexturePath = leaf.GetTexturePath();
		sk::Picture leafPicture(leafTexturePath);
		mRenderer.Draw(leaf.GetXCoord(), leaf.GetYCoord(), leafPicture);
	}

	for (auto& power : mPower) 
	{
		power.Fall(mFallSpeed);
		std::string powerTexturePath = power.GetTexturePath();
		sk::Picture powerPicture(powerTexturePath);
		mRenderer.Draw(power.GetXCoord(), power.GetYCoord(), powerPicture);
	}



	int fruitSpawnInterval = InitialFruitSpawnInterval - mFallSpeed / 10;
	fruitSpawnInterval = std::max(fruitSpawnInterval, 1);  

	if (mFruitsCaught > 5 && mFruitsCaught <= 25)
	{
		mFallSpeed = 15;
		InitialFruitSpawnInterval = 20;
	}
	else if (mFruitsCaught > 25) 
	{
		mFallSpeed = 20;
		InitialFruitSpawnInterval = 15;
	}
	else if (mFruitsCaught > 50)
	{
		mFallSpeed = 25;
		InitialFruitSpawnInterval = 12;
	}

	UpdatePower();

	mFrameCount++;

	CheckFruitCollision();
	CheckLeafCollision();
	CheckPowerCollision();
	DrawScore(100, 600, mScore);



}

void MyGame::HandleInput(const sk::KeyPressed& keyPressedEvent)
{
	int movementSpeed = mBasketSpeed;
	switch (keyPressedEvent.GetKeyCode())
	{
	case SKY_KEY_LEFT:
		mBasket.UpdateXCoord(-movementSpeed);
		break;
	case SKY_KEY_RIGHT:
		mBasket.UpdateXCoord(movementSpeed);
		break;
	default:
		break;
	}
}



void MyGame::AddFallingFruit()
{
	std::vector<std::string> fruitTexturePaths = {
		"../Assets/Pictures/apple.png",
		"../Assets/Pictures/banana.png",
		"../Assets/Pictures/pineapple.png",
		"../Assets/Pictures/strawberry.png",
		"../Assets/Pictures/orange.png",
		"../Assets/Pictures/watermelon.png",
		"../Assets/Pictures/grapes.png"
	};
	
	std::string randomTexturePath = fruitTexturePaths[RandomInt(0, fruitTexturePaths.size() - 1)];

	// Generate random position for fruit to fall 
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - mFruitSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - mFruitSize);
		randomY = mWindow.GetHeight();
	} while (IsOverlappingExistingObjects(randomX, randomY, mFruitSize));

	mFruits.emplace_back(randomTexturePath, randomX, randomY);


}

void MyGame::AddFallingLeaf()
{
	std::vector<std::string> leafTexturePaths = {
		"../Assets/Pictures/leaf1.png",
		"../Assets/Pictures/leaf2.png",
		"../Assets/Pictures/leaf3.png",
		"../Assets/Pictures/leaf4.png"
	};

	std::string randomTexturePath = leafTexturePaths[RandomInt(0, leafTexturePaths.size() - 1)];

	// Random position to fall  
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - mLeafSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - mLeafSize);
		randomY = mWindow.GetHeight();
	} while (IsOverlappingExistingObjects(randomX, randomY, mLeafSize));

	mLeaves.emplace_back(randomTexturePath, randomX, randomY);
}

void MyGame::AddFallingPower()
{
	std::vector<std::string> powerTexturePaths = {
		"../Assets/Pictures/power1.png",
		"../Assets/Pictures/power2.png"
	};

	std::string randomTexturePath = powerTexturePaths[RandomInt(0, powerTexturePaths.size() - 1)];

	// Random position to fall
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - mPowerSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - mPowerSize);
		randomY = RandomInt(mWindow.GetHeight() / 2, mWindow.GetHeight() - mPowerSize);
		randomY = std::clamp(randomY, mWindow.GetHeight() / 2, mWindow.GetHeight() - mPowerSize);
	} while (IsOverlappingExistingObjects(randomX, randomY, mPowerSize));

	mPower.emplace_back(randomTexturePath, randomX, randomY);
}

void MyGame::IncreaseSpeed()
{
	mBasketSpeed += 30;  
	mFallSpeed += 15;
	mCurrentTime = std::chrono::steady_clock::now();
}


void MyGame::UpdatePower()
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - mCurrentTime).count();

	if (elapsedTime >= 15)
	{
		// reset speed
		mBasketSpeed = 30;

	}
}

void MyGame::CheckFruitCollision()
{
	for (auto i = mFruits.begin(); i != mFruits.end();)
	{
		if (UnitsOverlap(*i, mBasket))
		{
			mScore += 50;
			mFruitsCaught++;
			i = mFruits.erase(i);
		} 
		else
		{
			++i;
		}
	}
}

void MyGame::CheckLeafCollision()
{
	for (auto i = mLeaves.begin(); i != mLeaves.end();)
	{
		if (UnitsOverlap(*i, mBasket))
		{
			mScore -= 25;
			mLeavesCaught++;
			i = mLeaves.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void MyGame::CheckPowerCollision()
{
	for (auto i = mPower.begin(); i != mPower.end();)
	{
		if (UnitsOverlap(*i, mBasket))
		{
			IncreaseSpeed();
			i = mPower.erase(i);
			UpdatePower();
		} 
		else
		{
			++i;
		}
	}

}


std::vector<sk::Picture> MyGame::LoadDigitTextures()
{
	std::vector<std::string> digitPaths;

	for (int i = 0; i <= 9; i++)
	{
		digitPaths.emplace_back("../Assets/Pictures/" + std::to_string(i) + ".png");
	}
	
	std::vector<sk::Picture> digitTextures;
	for (const auto& path : digitPaths)
	{
		digitTextures.emplace_back(path);
	}

	return digitTextures;

}


void MyGame::DrawScore(int x, int y, int score)
{
	std::vector<sk::Picture> digitTextures = LoadDigitTextures();

	if (score == 0) {
		mRenderer.Draw(x, y, digitTextures[0]);
		return;
	}

	// width of digits
	int totalWidth = 0;
	int tempScore = score;
	while (tempScore > 0) {
		int digit = tempScore % 10;
		totalWidth += digitTextures[digit].GetWidth();
		tempScore /= 10;
	}

	// draw from right of window
	int xOffset = x + totalWidth;

	// draw from right to left
	tempScore = score;
	while (tempScore > 0) {
		int digit = tempScore % 10;
		xOffset -= digitTextures[digit].GetWidth();
		mRenderer.Draw(xOffset, y, digitTextures[digit]);
		tempScore /= 10;
	}
}


bool MyGame::IsOverlappingExistingObjects(int x, int y, int objectSize)
{
	for (const auto& fruit : mFruits) {
		if (UnitsOverlap(fruit, x, y, objectSize)) {
			return true;
		}
	}

	for (const auto& leaf : mLeaves) {
		if (UnitsOverlap(leaf, x, y, objectSize)) {
			return true;
		}
	}

	for (const auto& power : mPower) {
		if (UnitsOverlap(power, x, y, objectSize)) {
			return true;
		}
	}

	return false;
}

int MyGame::RandomInt(int min, int max)
{
	// Initialize and generate random int
	auto currentTime = std::chrono::system_clock::now();
	auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
	srand(static_cast<unsigned int>(seed));
	return min + rand() % (max - min + 1);
}



