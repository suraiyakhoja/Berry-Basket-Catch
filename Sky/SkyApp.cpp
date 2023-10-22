#include "pch.h"
#include "SkyApp.h"

namespace sk
{
	template<typename T>
	SkyApp<T>::SkyApp()
	{
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
		mWindow.Create("Game_SK", 1000, 800);
		while (mShouldContinue)
		{
			OnUpdate();
			mWindow.SwapBuffers();
			mWindow.PollEvents();
		}

	}

	template<typename T>
	void SkyApp<T>::OnUpdate()
	{
	}
}