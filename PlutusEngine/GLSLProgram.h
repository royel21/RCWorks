#pragma once
#include <iostream>
#include <GL/glew.h>
namespace PlutusEngine {
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		//compile the shader file
		void compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath);
		//Link our shader together
		void linkShaders();

		void addAtribute(const std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();

		void unuse();

	private:
		int _numAtributes;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		void compileShader(const char* shaderdata, GLuint id);
	};

}