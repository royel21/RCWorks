#pragma once
#include <iostream>
#include <GL/glew.h>
#include <unordered_map>
#include <string>

namespace PlutusEngine {
	class GLSLProgram
	{
	private:
		int _numAtributes;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		std::unordered_map<std::string, GLint> uniformLocationsMap;

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
		void compileShader(const char* shaderdata, GLuint id);
	};

}