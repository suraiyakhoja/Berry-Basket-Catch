#include "pch.h"
#include "SkyApp.h"
#include "Utilities.h"
//#include "../glad/include/glad/glad.h"
//#include "../glfw/include/GLFW/glfw3.h"
//#include "../stbi/stb_image.h"
#include "Sky.h"
#include "Shader.h"
#include "Picture.h"
#include "Renderer.h"


namespace sk
{
	template<typename T>
	SkyApp<T>::SkyApp()
	{
		//mWindow.Create("Game_SK", 1000, 800);
		mWindow.Create("Game_SK", 1400, 800);
		mRenderer.Init();

		SetWindowCloseCallback([this]() {DefaultWindowCloseHandler(); }); // [](){}
	}

	template<typename T>
	void SkyApp<T>::Init()
	{
		if (sInstance == nullptr)
			sInstance = new T;
	}

	template<typename T>
	void SkyApp<T>::RunInterface()
	{
		sInstance->Run();
	}

	template<typename T>
	void SkyApp<T>::Run()
	{
		sk::Shader shader{ "../Assets/Shaders/DefaultVertexShader.glsl", "../Assets/Shaders/DefaultFragmentShader.glsl" };
		//sk::Picture pic{ "../Assets/Pictures/test.png" };

		mNextFrameTime = std::chrono::steady_clock::now();

		while (mShouldContinue)
		{
			mRenderer.Clear();

			shader.Bind();
			shader.SetUniform2Ints("ScreenSize", mWindow.GetWidth(), mWindow.GetHeight());

			//pic.Bind();
			//mRenderer.Draw(0, 0, pic);

			OnUpdate();

			std::this_thread::sleep_until(mNextFrameTime);
			mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;

			mWindow.SwapBuffers();
			mWindow.PollEvents();

		}

	}

	template<typename T>
	void SkyApp<T>::OnUpdate()
	{
	}

	template<typename T>
	void SkyApp<T>::Draw(int x, int y, Picture& pic)
	{
		sInstance->mRenderer.Draw(x, y, pic);
	}

	template<typename T>
	void SkyApp<T>::Draw(Unit& item)
	{
		sInstance->mRenderer.Draw(item.mXPosition, item.mYPosition, item.mImage);
	}

	template<typename T>
	void SkyApp<T>::SetKeyPressedCallback(std::function<void(const KeyPressed&)> callbackFunc)
	{
		mWindow.SetKeyPressedCallback(callbackFunc);
	}

	template<typename T>
	void SkyApp<T>::SetKeyReleasedCallback(std::function<void(const KeyReleased&)> callbackFunc)
	{
		mWindow.SetKeyReleasedCallback(callbackFunc);
	}

	template<typename T>
	void SkyApp<T>::SetWindowCloseCallback(std::function<void()> callbackFunc)
	{
		mWindow.SetWindowCloseCallback(callbackFunc);
	}

	template<typename T>
	void SkyApp<T>::DefaultWindowCloseHandler()
	{
		mShouldContinue = false;
	}


}