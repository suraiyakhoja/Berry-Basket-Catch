#include "pch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"



#include "OpenGLPicture.h"

#include "../Utilities.h"

namespace sk
{
	OpenGLPicture::OpenGLPicture(const std::string& fileName)
	{
		glGenTextures(1, &mTexture);
		Bind();
		//glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



		// Load image from file
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			std::cout << "PIC WIDTH!!!" << width << std::endl;
			std::cout << "PIC HEIGHT" << height << std::endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			mWidth = width;
			mHeight = height;


			
		}
		else
		{
			SK_ERROR("Failed to load a picture from the file!!!");
		}
		stbi_image_free(data);

	}

	OpenGLPicture::OpenGLPicture(std::string&& fileName)
	{
		glGenTextures(1, &mTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Load image from file
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(move(fileName).c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			mWidth = width;
			mHeight = height;
		}
		else
		{
			SK_ERROR("Failed to load a picture from the file!!!");
		}
		stbi_image_free(data);

	}

	OpenGLPicture::~OpenGLPicture()
	{
		glDeleteTextures(1, &mTexture);
	}

	void OpenGLPicture::Bind()
	{
		/*
		glBindTexture(GL_TEXTURE_2D, mTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		*/
		glBindTexture(GL_TEXTURE_2D, mTexture);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  // Set minification filter
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture

	}


	int OpenGLPicture::GetWidth() const
	{
		return mWidth;
	}

	int OpenGLPicture::GetHeight() const
	{
		return mHeight;
	}
}