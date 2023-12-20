#include "pch.h"
#include "Picture.h"
#include "GLFWCode/OpenGLPicture.h"

namespace sk
{
	Picture::Picture(const std::string& fileName)
	{
#ifdef SKY_MSCPP
		mImplementation = std::unique_ptr<PictureImplementation>{ new OpenGLPicture(fileName) };
#elif SKY_APPLE
		mImplementation = std::unique_ptr<PictureImplementation>{ new OpenGLPicture(fileName) };
#elif SKY_LINUX
		mImplementation = std::unique_ptr<PictureImplementation>{ new OpenGLPicture(fileName) };
#endif
	}


	void Picture::Bind()
	{
		mImplementation->Bind();
	}

	int Picture::GetWidth() const
	{
		return mImplementation->GetWidth();
	}

	int Picture::GetHeight() const
	{
		return mImplementation->GetHeight();
	}

}