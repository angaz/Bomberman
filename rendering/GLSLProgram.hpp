#ifndef NEW_GLSLPROGRAM_HPP
#define NEW_GLSLPROGRAM_HPP

#include <string>

#include <glm/glm.hpp>

#include "../loaders/IO.hpp"

namespace cge {
	class GLSLProgram {
	public:
		GLSLProgram(const std::string &vertexFilePath, const std::string &fragmentFilePath);
		~GLSLProgram() = default;

		bool	compileShaders(const std::string &vertexFilePath, const std::string &fragmentFilePath);
		bool	linkProgram();
		void	begin();
		void	end();
		void	bindAttribute(const std::string &attributeName);

		GLint	getUniformLocation(const std::string &uniformName) const;
		GLint	getAttributeLocation(const std::string &attrName) const;
		void	upload1i(GLint location, GLint value) const;
		void	uploadFloat(GLint location, float value) const;
		void	uploadvec3d(GLint location, const glm::vec3 &value) const;
		void	uploadvec2d(GLint location, const glm::vec2 &value) const;
		void	uploadBool(GLint location, bool value) const;
		void	uploadBool(const std::string &uniformName, bool value) const;
		void	uploadMatrix4f(GLint location, const glm::mat4 &value) const;
		void	uploadMatrix4f(GLint location, const std::vector<glm::mat4> &value) const;
		void	uploadMatrix4f(const std::string &uniformName, const glm::mat4 &value) const;
		bool	isInUse() const;

	private:
		GLuint		_vertexShaderID;
		GLuint		_fragmentShaderID;
		GLuint		_programID;
		unsigned	_attributeCount;
		bool 		_isInUse;

		bool 		_compileShader(const std::string &shaderSRC, GLuint shaderID);
		void		_checkInUse() const;
	};
}

#endif //NEW_GLSLPROGRAM_HPP
