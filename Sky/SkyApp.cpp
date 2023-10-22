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
		while (mShouldContinue)
		{
			OnUpdate();
		}

	}

	template<typename T>
	void SkyApp<T>::OnUpdate()
	{
	}
}