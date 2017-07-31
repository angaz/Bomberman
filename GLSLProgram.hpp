#ifndef NEW_GLSLPROGRAM_HPP
#define NEW_GLSLPROGRAM_HPP

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "IO.hpp"

class GLSLProgram {
public:
	GLSLProgram();
	~GLSLProgram() = default;

	bool	compileShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath);
	bool	linkProgram();
	void	bindAttribute(const std::string &attributeName);
	void	start();
	void	end();
	GLint	getUniformLocation(const std::string &uniformName);
	void	uploadFloat(GLint location, float value);
	void	uploadvec3d(GLint location, const glm::vec3 &value);
	void	uploadBool(GLint location, bool value);
	void	uploadMatrix4f(GLint location, const glm::mat4 &value);

private:
	GLuint	_vertexShaderID;
	GLuint	_fragmentShaderID;
	GLuint	_programID;
	unsigned	_attributeCount;

	bool 		_compileShader(const std::string &shaderSRC, GLuint shaderID);
};


#endif //NEW_GLSLPROGRAM_HPP