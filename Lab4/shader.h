////#pragma once
////#ifndef SHADER_H
////#define SHADER_H
////
////#include <glm/glm.hpp>
////
////#include <string>
////#include <fstream>
////#include <sstream>
////#include <iostream>
////#include <GL/glew.h>
////
////class Shader
////{
////public:
////	unsigned int ID;
////	// constructor generates the shader on the fly
////	// ------------------------------------------------------------------------
////	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
////	{
////		// 1. retrieve the vertex/fragment source code from filePath
////		std::string vertexCode;
////		std::string fragmentCode;
////		std::string geometryCode;
////		std::ifstream vShaderFile;
////		std::ifstream fShaderFile;
////		std::ifstream gShaderFile;
////		// ensure ifstream objects can throw exceptions:
////		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
////		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
////		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
////		try
////		{
////			// open files
////			vShaderFile.open(vertexPath);
////			fShaderFile.open(fragmentPath);
////			std::stringstream vShaderStream, fShaderStream;
////			// read file's buffer contents into streams
////			vShaderStream << vShaderFile.rdbuf();
////			fShaderStream << fShaderFile.rdbuf();
////			// close file handlers
////			vShaderFile.close();
////			fShaderFile.close();
////			// convert stream into string
////			vertexCode = vShaderStream.str();
////			fragmentCode = fShaderStream.str();
////			// if geometry shader path is present, also load a geometry shader
////			if (geometryPath != nullptr)
////			{
////				gShaderFile.open(geometryPath);
////				std::stringstream gShaderStream;
////				gShaderStream << gShaderFile.rdbuf();
////				gShaderFile.close();
////				geometryCode = gShaderStream.str();
////			}
////		}
////		catch (std::ifstream::failure e)
////		{
////			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
////		}
////		const char* vShaderCode = vertexCode.c_str();
////		const char * fShaderCode = fragmentCode.c_str();
////		// 2. compile shaders
////		unsigned int vertex, fragment;
////		// vertex shader
////		vertex = glCreateShader(GL_VERTEX_SHADER);
////		glShaderSource(vertex, 1, &vShaderCode, NULL);
////		glCompileShader(vertex);
////		checkCompileErrors(vertex, "VERTEX");
////		// fragment Shader
////		fragment = glCreateShader(GL_FRAGMENT_SHADER);
////		glShaderSource(fragment, 1, &fShaderCode, NULL);
////		glCompileShader(fragment);
////		checkCompileErrors(fragment, "FRAGMENT");
////		// if geometry shader is given, compile geometry shader
////		unsigned int geometry;
////		if (geometryPath != nullptr)
////		{
////			const char * gShaderCode = geometryCode.c_str();
////			geometry = glCreateShader(GL_GEOMETRY_SHADER);
////			glShaderSource(geometry, 1, &gShaderCode, NULL);
////			glCompileShader(geometry);
////			checkCompileErrors(geometry, "GEOMETRY");
////		}
////		// shader Program
////		ID = glCreateProgram();
////		glAttachShader(ID, vertex);
////		glAttachShader(ID, fragment);
////		if (geometryPath != nullptr)
////			glAttachShader(ID, geometry);
////		glLinkProgram(ID);
////		checkCompileErrors(ID, "PROGRAM");
////		// delete the shaders as they're linked into our program now and no longer necessery
////		glDeleteShader(vertex);
////		glDeleteShader(fragment);
////		if (geometryPath != nullptr)
////			glDeleteShader(geometry);
////
////	}
////	// activate the shader
////	// ------------------------------------------------------------------------
////	void use()
////	{
////		glUseProgram(ID);
////	}
////	// utility uniform functions
////	// ------------------------------------------------------------------------
////	void setBool(const std::string &name, bool value) const
////	{
////		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
////	}
////	// ------------------------------------------------------------------------
////	void setInt(const std::string &name, int value) const
////	{
////		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
////	}
////	// ------------------------------------------------------------------------
////	void setFloat(const std::string &name, float value) const
////	{
////		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
////	}
////	// ------------------------------------------------------------------------
////	void setVec2(const std::string &name, const glm::vec2 &value) const
////	{
////		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
////	}
////	void setVec2(const std::string &name, float x, float y) const
////	{
////		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
////	}
////	// ------------------------------------------------------------------------
////	void setVec3(const std::string &name, const glm::vec3 &value) const
////	{
////		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
////	}
////	void setVec3(const std::string &name, float x, float y, float z) const
////	{
////		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
////	}
////	// ------------------------------------------------------------------------
////	void setVec4(const std::string &name, const glm::vec4 &value) const
////	{
////		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
////	}
////	void setVec4(const std::string &name, float x, float y, float z, float w)
////	{
////		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
////	}
////	// ------------------------------------------------------------------------
////	void setMat2(const std::string &name, const glm::mat2 &mat) const
////	{
////		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
////	}
////	// ------------------------------------------------------------------------
////	void setMat3(const std::string &name, const glm::mat3 &mat) const
////	{
////		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
////	}
////	// ------------------------------------------------------------------------
////	void setMat4(const std::string &name, const glm::mat4 &mat) const
////	{
////		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
////	}
////
////private:
////	// utility function for checking shader compilation/linking errors.
////	// ------------------------------------------------------------------------
////	void checkCompileErrors(GLuint shader, std::string type)
////	{
////		GLint success;
////		GLchar infoLog[1024];
////		if (type != "PROGRAM")
////		{
////			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
////			if (!success)
////			{
////				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
////				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
////			}
////		}
////		else
////		{
////			glGetProgramiv(shader, GL_LINK_STATUS, &success);
////			if (!success)
////			{
////				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
////				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
////			}
////		}
////	}
////};
////#endif
//
//
//#ifndef SHADER_H
//#define SHADER_H
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//#include <GL/glew.h>
//
//class Shader
//{
//public:
//	GLuint Program;
//	// Constructor generates the shader on the fly
//	Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
//	{
//		// 1. Retrieve the vertex/fragment source code from filePath
//		std::string vertexCode;
//		std::string fragmentCode;
//		std::ifstream vShaderFile;
//		std::ifstream fShaderFile;
//		// ensures ifstream objects can throw exceptions:
//		vShaderFile.exceptions(std::ifstream::badbit);
//		fShaderFile.exceptions(std::ifstream::badbit);
//		try
//		{
//			// Open files
//			vShaderFile.open(vertexPath);
//			fShaderFile.open(fragmentPath);
//			std::stringstream vShaderStream, fShaderStream;
//			// Read file's buffer contents into streams
//			vShaderStream << vShaderFile.rdbuf();
//			fShaderStream << fShaderFile.rdbuf();
//			// close file handlers
//			vShaderFile.close();
//			fShaderFile.close();
//			// Convert stream into string
//			vertexCode = vShaderStream.str();
//			fragmentCode = fShaderStream.str();
//		}
//		catch (std::ifstream::failure e)
//		{
//			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//		}
//		const GLchar *vShaderCode = vertexCode.c_str();
//		const GLchar *fShaderCode = fragmentCode.c_str();
//		// 2. Compile shaders
//		GLuint vertex, fragment;
//		GLint success;
//		GLchar infoLog[512];
//		// Vertex Shader
//		vertex = glCreateShader(GL_VERTEX_SHADER);
//		glShaderSource(vertex, 1, &vShaderCode, NULL);
//		glCompileShader(vertex);
//		// Print compile errors if any
//		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//		}
//		// Fragment Shader
//		fragment = glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fragment, 1, &fShaderCode, NULL);
//		glCompileShader(fragment);
//		// Print compile errors if any
//		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		}
//		// Shader Program
//		this->Program = glCreateProgram();
//		glAttachShader(this->Program, vertex);
//		glAttachShader(this->Program, fragment);
//		glLinkProgram(this->Program);
//		// Print linking errors if any
//		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//		}
//		// Delete the shaders as they're linked into our program now and no longer necessery
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//
//	}
//	// Uses the current shader
//	void Use()
//	{
//		glUseProgram(this->Program);
//	}
//};
//
//#endif


#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	// constructor generates the shader on the fly
	Shader(const char *vertexPath, const char *fragmentPath,
		const char *geometryPath = nullptr);

	void use();

	// Utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;

	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;

	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);

	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

	void setUniformMatrix4fv(const char* uniformName, const GLfloat *data);

	unsigned int getId();

private:
	unsigned int id;

	
	void checkCompileErrors(GLuint shader, std::string type);
};
#endif // !SHADER_H
