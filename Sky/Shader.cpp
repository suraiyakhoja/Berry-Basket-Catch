#include "pch.h"
#include "Shader.h"
#include "GLFWCode/OpenGLShader.h"

namespace sk
{
	Shader::Shader(const std::string& vertexSFile, const std::string& fragmentSFile)
	{
		//create a new object of openGL shader 

#ifdef SKY_MSCPP
		mImplementation = std::unique_ptr<ShaderImplementation>{ new OpenGLShader(vertexSFile, fragmentSFile) };
#elif SKY_APPLE
		mImplementation = std::unique_ptr<ShaderImplementation>{ new OpenGLShader(vertexSFile, fragmentSFile) };
#elif SKY_LINUX
		mImplementation = std::unique_ptr<ShaderImplementation>{ new OpenGLShader(vertexSFile, fragmentSFile) };
#endif
	}


	
	void Shader::Bind()
	{
		mImplementation->Bind(); 
	}
	void Shader::SetUniform2Ints(const std::string& uniformName, int val1, int val2)
	{
		mImplementation->SetUniform2Ints(uniformName, val1, val2);
	}
	void Shader::SetUniform2Ints(std::string&& uniformName, int val1, int val2)
	{
		mImplementation->SetUniform2Ints(std::move(uniformName), val1, val2);
	}
}