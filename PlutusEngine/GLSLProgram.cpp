#include "GLSLProgram.h"
#include "Errors.h"

#include <string>
#include <fstream>
#include <vector>

namespace PlutusEngine {
	GLSLProgram::GLSLProgram() :
		_numAtributes(0),
		_programID(0),
		_vertexShaderID(0),
		_fragmentShaderID(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programID = glCreateProgram();
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (!_vertexShaderID) {

			PlutusEngine::fatalError("vertex fail to be created!");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (!_fragmentShaderID) {

			PlutusEngine::fatalError("fragment fail to be created!");
		}

		compileShader(vertexShaderPath, _vertexShaderID);
		compileShader(fragmentShaderPath, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders()
	{

		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			// Use the infoLog as you see fit.
			std::printf("%s\n", &(errorLog[0]));
			PlutusEngine::fatalError("shader fail to link");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

	}

	void GLSLProgram::addAtribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAtributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		if (uniformLocationsMap.find(uniformName) != uniformLocationsMap.end())
			return uniformLocationsMap[uniformName];

		GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			PlutusEngine::fatalError("Uniform " + uniformName + " not found in shader");
		}
		uniformLocationsMap[uniformName] = location;

		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAtributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAtributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void GLSLProgram::compileShader(const char* shaderdata, GLuint id)
	{
		glShaderSource(id, 1, &shaderdata, nullptr);

		GLint success = 0;
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(id); // Don't leak the shader.

			std::printf("%s\n", &(errorLog[0]));
			PlutusEngine::fatalError(shaderdata);
		}
	}
}