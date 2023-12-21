#include "MyGame.h"
//#include "Keys.h"

MyGame::MyGame() :
	mBasket("../Assets/Pictures/basket.png", 0, 0), mBasketTexture("../Assets/Pictures/basket.png"),
	//mApple("../Assets/Pictures/apple.png", 15, 15), mAppleTexture("../Assets/Pictures/apple.png"),
	mFrameCount(0), mFallSpeed(10), mFruitsCaught(0), mScore(0), mFallingFruits(1)
{
	//mBasketTexture = sk::Picture("../Assets/Pictures/basket.png");
	//mAppleTexture = sk::Picture("../Assets/Pictures/apple.png");
}

void MyGame::OnUpdate()
{
	std::cout << "OnUpdate" << std::endl;
	mRenderer.Clear();
	sk::Picture backgroundPicture("../Assets/Pictures/background.png");
	mRenderer.Draw(0, 0, backgroundPicture);


	mRenderer.Draw(mBasket.GetXCoord(), mBasket.GetYCoord(), mBasketTexture);
	std::cout << "Basket Coordinates: (" << mBasket.GetXCoord() << ", " << mBasket.GetYCoord() << ")" << std::endl;
	std::cout << "mFallingFruits: " << mFallingFruits << ", InitialFruitSpawnInterval: " << InitialFruitSpawnInterval << std::endl;


	if (mFrameCount % (InitialFruitSpawnInterval / mFallingFruits) == 0) {
		AddFallingFruit();
		std::cout << "Number of Fruits: " << mFruits.size() << std::endl;

	}
	
	if (mFruitsCaught >= 5 && mFrameCount % mLeafSpawnInterval == 0)
	{
		AddFallingLeaf();
		std::cout << "Number of Leaves: " << mLeaves.size() << std::endl;
	}

	if (mFruitsCaught >= 10 && mFrameCount % 20 == 0)
	{
		// Spawn a power texture every 20 frames when 25 fruits have been caught
		if (mFruitsCaught % 5 == 0)
		{
			AddFallingPower();
		}
	}
	
	

	for (auto& fruit : mFruits) {
		std::cout << "Fruit Coordinates: (" << fruit.GetXCoord() << ", " << fruit.GetYCoord() << ")" << std::endl;

		fruit.Fall(mFallSpeed);
		std::string fruitTexturePath = fruit.GetTexturePath();
		sk::Picture fruitPicture(fruitTexturePath); // Convert the path to a Picture

		mRenderer.Draw(fruit.GetXCoord(), fruit.GetYCoord(), fruitPicture);
	}
	
	for (auto& leaf : mLeaves) {
		std::cout << "Leaf Coordinates: (" << leaf.GetXCoord() << ", " << leaf.GetYCoord() << ")" << std::endl;
		leaf.Fall(mFallSpeed);
		std::string leafTexturePath = leaf.GetTexturePath();
		sk::Picture leafPicture(leafTexturePath);
		mRenderer.Draw(leaf.GetXCoord(), leaf.GetYCoord(), leafPicture);
	}

	for (auto& power : mPower) {
		power.Fall(mFallSpeed);
		std::string powerTexturePath = power.GetTexturePath();
		sk::Picture powerPicture(powerTexturePath);
		mRenderer.Draw(power.GetXCoord(), power.GetYCoord(), powerPicture);
	}


	
	

	int fruitSpawnInterval = InitialFruitSpawnInterval - mFallSpeed / 10;
	fruitSpawnInterval = std::max(fruitSpawnInterval, 1);  // Ensure the interval is not less than 1
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

	

	UpdatePower();


	
	mFrameCount++;

	CheckFruitCollision();
	CheckLeafCollision();
	CheckPowerCollision();
	UpdateScore();
	DrawScore(700, 500, mScore);



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
		// Add more fruit textures as needed
	};

	std::string randomTexturePath = fruitTexturePaths[RandomInt(0, fruitTexturePaths.size() - 1)];

	// Generate a random position for the fruit, avoiding overlap
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - FruitSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - FruitSize);
		randomY = mWindow.GetHeight();
	} while (IsOverlappingExistingObjects(randomX, randomY, FruitSize));

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

	// Generate a random position for the leaf, avoiding overlap
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - LeafSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - LeafSize);
		randomY = mWindow.GetHeight();
	} while (IsOverlappingExistingObjects(randomX, randomY, LeafSize));

	mLeaves.emplace_back(randomTexturePath, randomX, randomY);
}

void MyGame::DrawScore(int x, int y, int score)
{
	std::vector<sk::Picture> digitTextures = LoadDigitTextures();

	// Handle the case when the score is 0
	if (score == 0) {
		mRenderer.Draw(x, y, digitTextures[0]);
		return;
	}

	// Calculate the total width of the digits
	int totalWidth = 0;
	int tempScore = score;
	while (tempScore > 0) {
		int digit = tempScore % 10;
		totalWidth += digitTextures[digit].GetWidth();
		tempScore /= 10;
	}

	// Start drawing from the right side of the window
	int xOffset = x + totalWidth;

	// Draw each digit from right to left
	tempScore = score;
	while (tempScore > 0) {
		int digit = tempScore % 10;
		xOffset -= digitTextures[digit].GetWidth();
		mRenderer.Draw(xOffset, y, digitTextures[digit]);
		tempScore /= 10;
	}
}








std::vector<sk::Picture> MyGame::LoadDigitTextures()
{
	std::vector<std::string> digitPaths;
	//Load textures for digits and store them in digitTextures

	for (int i = 0; i <= 9; i++)
	{
		
		digitPaths.emplace_back("../Assets/Pictures/" + std::to_string(i) + ".png");
	}
	// Create sk::Picture objects when needed
	std::vector<sk::Picture> digitTextures;
	for (const auto& path : digitPaths)
	{
		digitTextures.emplace_back(path);
	}

	return digitTextures;

}

int MyGame::RandomInt(int min, int max)
{
	//first three lines extra 
	auto currentTime = std::chrono::system_clock::now();
	auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

	// Seed the random number generator
	srand(static_cast<unsigned int>(seed));
	return min + rand() % (max - min + 1);
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
		else {
			++i; // no collision, move to next fruit 
		}
	}
}

void MyGame::CheckLeafCollision()
{
	for (auto i = mLeaves.begin(); i != mLeaves.end();)
	{
		if (UnitsOverlap(*i, mBasket))
		{
			mScore -= 50;
			mLeavesCaught++;
			i = mLeaves.erase(i);
		}
		else {
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
		else {
			++i;
		}
	}

}

void MyGame::AddFallingPower()
{
	std::vector<std::string> powerTexturePaths = {
		"../Assets/Pictures/power1.png",
		"../Assets/Pictures/power2.png"
	};

	std::string randomTexturePath = powerTexturePaths[RandomInt(0, powerTexturePaths.size() - 1)];

	// Generate a random position for the power-up, avoiding overlap
	int randomX, randomY;
	do {
		randomX = RandomInt(0, mWindow.GetWidth() - PowerSize);
		randomX = std::clamp(randomX, 0, mWindow.GetWidth() - PowerSize);
		randomY = RandomInt(mWindow.GetHeight() / 2, mWindow.GetHeight() - PowerSize);
		randomY = std::clamp(randomY, mWindow.GetHeight() / 2, mWindow.GetHeight() - PowerSize);
	} while (IsOverlappingExistingObjects(randomX, randomY, PowerSize));

	mPower.emplace_back(randomTexturePath, randomX, randomY);
}


void MyGame::UpdateScore()
{
	std::cout << "Score: " << mScore << std::endl;
}

void MyGame::IncreaseSpeed()
{
	// Adjust the speed based on your requirements
	mBasketSpeed += 30;  // Increase by 15 (you can adjust this value)
	mFallSpeed += 15;
	mCurrentTime = std::chrono::steady_clock::now();
}

void MyGame::UpdatePower()
{
	auto currentTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - mCurrentTime).count();

	if (elapsedTime >= 7)
	{
		// Reset the speed to its original value
		mBasketSpeed = 30;

	}
}

bool MyGame::IsOverlappingExistingObjects(int x, int y, int objectSize)
{
	// Check if the new object overlaps with any existing objects
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

	// No overlap with existing objects
	return false;
}

