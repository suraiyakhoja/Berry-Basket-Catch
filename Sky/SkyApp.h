#pragma once

#include "Utilities.h"

namespace sk
{
	template<typename T>
	class SKY_API SkyApp
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
		bool mShouldContinue{ true };

	};
};

#include "SkyApp.cpp"

