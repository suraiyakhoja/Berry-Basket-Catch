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


	if (mFrameCount % (InitialFruitSpawnInterval / mFallingFruits) == 0) {
		AddFallingFruit();
		std::cout << "Number of Fruits: " << mFruits.size() << std::endl;

	}

	for (auto& fruit : mFruits) {
		std::cout << "Fruit Coordinates: (" << fruit.GetXCoord() << ", " << fruit.GetYCoord() << ")" << std::endl;

		fruit.Fall(mFallSpeed);
		std::string fruitTexturePath = fruit.GetTexturePath();
		sk::Picture fruitPicture(fruitTexturePath); // Convert the path to a Picture
	

		mRenderer.Draw(fruit.GetXCoord(), fruit.GetYCoord(), fruitPicture);
	}
	

	int fruitSpawnInterval = InitialFruitSpawnInterval - mFallSpeed / 10;
	fruitSpawnInterval = std::max(fruitSpawnInterval, 1);  // Ensure the interval is not less than 1
	if (mFruitsCaught > 5)
	{
		mFallSpeed = 15;
		InitialFruitSpawnInterval = 20;
	}

	
	mFrameCount++;

	CheckCollision();
	UpdateScore();
	DrawScore(700, 500, mScore);



}

void MyGame::HandleInput(const sk::KeyPressed& keyPressedEvent)
{
	constexpr int movementSpeed = 30;
	switch (keyPressedEvent.GetKeyCode())
	{
	case SKY_KEY_LEFT:
		mBasket.UpdateXCoord(-movementSpeed);
		break;
	case SKY_KEY_RIGHT:
		mBasket.UpdateXCoord(movementSpeed);
		break;
	case SKY_KEY_UP:
		mBasket.UpdateYCoord(movementSpeed);
		break;
	case SKY_KEY_DOWN:
		mBasket.UpdateYCoord(-movementSpeed);
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
		"../Assets/Pictures/strawberry.png"
		// Add more fruit textures as needed
	};

	// Randomly select a fruit texture path
	std::string randomTexturePath = fruitTexturePaths[RandomInt(0, fruitTexturePaths.size() - 1)];


	int randomX = RandomInt(0, mWindow.GetWidth() - FruitSize);
	randomX = std::clamp(randomX, 0, mWindow.GetWidth() - FruitSize);
	mFruits.emplace_back(randomTexturePath, randomX, mWindow.GetHeight());







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

void MyGame::CheckCollision()
{
	for (auto i = mFruits.begin(); i != mFruits.end();)
	{
		if (UnitsOverlap(*i, mBasket))
		{
			mScore++;
			mFruitsCaught++;
			i = mFruits.erase(i);
		}
		else {
			++i; // no collision, move to next fruit 
		}
	}
}

void MyGame::UpdateScore()
{
	std::cout << "Score: " << mScore << std::endl;
}

