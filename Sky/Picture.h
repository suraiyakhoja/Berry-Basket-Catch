#pragma once

#include "pch.h"
#include "Utilities.h"
#include "PictureImplementation.h"

namespace sk
{
	class SKY_API Picture
	{
	public:
		Picture(const std::string& fileName);

		void Bind();
		int GetWidth() const;
		int GetHeight() const;

		//virtual ~Picture();

	private:
		std::unique_ptr<PictureImplementation> mImplementation;
	};
}