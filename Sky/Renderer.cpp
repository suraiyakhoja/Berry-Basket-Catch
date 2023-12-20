#include "pch.h"
#include "Renderer.h"
#include "GLFWCode/OpenGLRenderer.h"

sk::Renderer::Renderer()
{
#ifdef SKY_MSCPP
	mImplementation = std::unique_ptr<RendererImplementation>{ new OpenGLRenderer };
#elif SKY_APPLE 
	mImplementation = std::unique_ptr<RendererImplementation>{ new OpenGLRenderer };
#elif SKY_LINUX
	mImplementation = std::unique_ptr<RendererImplementation>{ new OpenGLRenderer };
#endif
}

void sk::Renderer::Init()
{
	mImplementation->Init();
}

void sk::Renderer::Draw(int x, int y, Picture& pic)
{
	mImplementation->Draw(x, y, pic);
}

void sk::Renderer::Clear()
{
	mImplementation->Clear();
}