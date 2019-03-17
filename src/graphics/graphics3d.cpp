/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <sstream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <graphics/graphics3d.h>
#include "utility/file_utility.h"
#include "utility/log.h"

namespace sfge
{

void Shader::Init(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const auto vertexShaderProgram = LoadFile(vertexShaderPath);
	const char* vertexShaderChar = vertexShaderProgram.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderChar, NULL);
	glCompileShader(vertexShader);
	//Check success status of shader compilation 
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::ostringstream oss;
		oss << "[Error] Vertex Shader Compilation for "<< vertexShaderPath <<"\n" << infoLog;
		Log::GetInstance()->Error(oss.str());
		return;
	}

	const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	auto fragmentShaderProgram = LoadFile(fragmentShaderPath);
	const char* fragmentShaderChar = fragmentShaderProgram.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderChar, NULL);
	glCompileShader(fragmentShader);
	//Check success status of shader compilation 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::ostringstream oss;
		oss << "[Error] Fragment Shader Compilation for " << fragmentShaderPath << "\n" << infoLog;
		Log::GetInstance()->Error(oss.str());
		return;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//Check if shader program was linked correctly
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "[Error] Shader" << vertexShaderPath << " and "<<fragmentShaderPath<<" link error\n" << infoLog << std::endl;
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Bind()
{
	glUseProgram(shaderProgram);
}

int Shader::GetProgram()
{
	return shaderProgram;
}
}