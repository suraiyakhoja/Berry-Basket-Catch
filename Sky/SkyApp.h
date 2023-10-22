#pragma once

#include "Utilities.h"
#include "GameWindow.h"

namespace sk
{
	template<typename T>
	class SkyApp
	{
	public:
		static void Init();
		static void RunInterface();

		void Run();
		virtual void OnUpdate();

		friend typename T;

	private:
		SkyApp();
		inline static SkyApp* sInstance{ nullptr };
		GameWindow mWindow;
		bool mShouldContinue{ true };

	};
};

#include "SkyApp.cpp"

