#include "pch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "OpenGLShader.h"

#include "../Utilities.h"


namespace sk
{
	OpenGLShader::OpenGLShader(const std::string& vertexSF, const std::string& fragmentSF)
	{
		std::string vertexString{ ReadWholeFile(vertexSF) };
		const char* vertexShaderSource = vertexString.c_str();
		std::string fragmentString{ ReadWholeFile(fragmentSF) };
		const char* fragmentShaderSource = fragmentString.c_str();

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR SHADER VERTEX COMPILATIN" << std::endl;
			SK_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
		}

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			SK_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog);
			std::cout << "fragment shader error" << std::endl;
		}

		//unsigned int shaderProgram; --- replaced by class member variable 
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, vertexShader);
		glAttachShader(mShaderProgram, fragmentShader);
		glLinkProgram(mShaderProgram);

		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
			std::cout << "linking error" << std::endl;
			SK_ERROR("Linking FAILED with the message: " << infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::OpenGLShader(std::string&& vertexSF, std::string&& fragmentSF)
	{
		std::string vertexString{ ReadWholeFile(move(vertexSF)) };
		const char* vertexShaderSource = vertexString.c_str();
		std::string fragmentString{ ReadWholeFile(move(fragmentSF)) };
		const char* fragmentShaderSource = fragmentString.c_str();

		std::cout << vertexShaderSource << std::endl;
		std::cout << fragmentShaderSource << std::endl;

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "shader vertex compilation error" << std::endl;
			SK_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
		}

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "fragment shader error" << std::endl;
			SK_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog);
		}

		//unsigned int shaderProgram; --- replaced by class member variable 
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, vertexShader);
		glAttachShader(mShaderProgram, fragmentShader);
		glLinkProgram(mShaderProgram);

		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
			std::cout << "linking error" << std::endl;
			SK_ERROR("Linking FAILED with the message: " << infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(mShaderProgram);
	}


	void OpenGLShader::Bind()
	{
		glUseProgram(mShaderProgram);
	}

	void OpenGLShader::SetUniform2Ints(const std::string& uniformName, int val1, int val2)
	{
		glUseProgram(mShaderProgram);
		GLint location{ glGetUniformLocation(mShaderProgram, uniformName.c_str()) };
		glUniform2i(location, val1, val2);
	}

	void OpenGLShader::SetUniform2Ints(std::string&& uniformName, int val1, int val2)
	{
		glUseProgram(mShaderProgram);
		GLint location{ glGetUniformLocation(mShaderProgram, uniformName.c_str()) };
		glUniform2i(location, val1, val2);
	}

	std::string OpenGLShader::ReadWholeFile(const std::string& fileName)
	{
		std::ifstream inputFile{ fileName };// input file stream object of ifstream class. constructor with string. 
		
		std::string result;
		std::string nextLine;

		while (inputFile) // returns true if there is no end of file/error flag raised. true if file reading is still possible. 
		{
			std::getline(inputFile, nextLine); // read next line from the line.
			if (!inputFile)
				break;
			result += nextLine;// add next line to final result
			result += "\n"; //  getline function doesn't read end of line symbol  
		}
		return result;
	
	}
	std::string OpenGLShader::ReadWholeFile(std::string&& fileName)
	{
		std::ifstream inputFile{ move(fileName) };// input file stream object of ifstream class. constructor with string. 

		std::string result;
		std::string nextLine;

		while (inputFile) // returns true if there is no end of file/error flag raised. true if file reading is still possible. 
		{
			std::getline(inputFile, nextLine); // read next line from the line.
			if (!inputFile)
				break;
			result += nextLine;// add next line to final result
			result += "\n"; //  getline function doesn't read end of line symbol  
		}
		return result;
	}
}