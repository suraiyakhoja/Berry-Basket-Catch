#pragma once

#include "pch.h"
#include "PictureImplementation.h"

namespace sk
{
	class OpenGLPicture : public PictureImplementation
	{
	public:
		OpenGLPicture(const std::string& fileName);
		OpenGLPicture(std::string&& fileName);
		~OpenGLPicture();

		void Bind() override;

		virtual int GetWidth() const override;
		virtual int GetHeight() const override;


	private:
		unsigned int mTexture;
		int mWidth;
		int mHeight;
	};
}