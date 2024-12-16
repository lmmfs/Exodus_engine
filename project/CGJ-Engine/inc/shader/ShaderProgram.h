#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "GL/glew.h"

namespace engine {

	/**
	* Shader program class
	*
	*/
	class ShaderProgram {

	private:

		GLuint ProgramId = 0;
		float isShadowShader = 0;

		std::map<std::string, GLuint> uniforms;

		const std::map<std::string, const int> bindings = {
			{ "VERTICES",	0 },
			{ "COLORS",		1 },
			{ "TEX_COORDS",	2 },
			{ "NORMALS",	3 },
			{ "UBO_BP",		0 }
		};

		void Init(const char*, const char*);
		void InitShadow(const char*, const char*);
		void InitSkyBox(const char*, const char*);

		/**
		* Checks the shader for compilation errors
		*
		* @param GLuint the shader id
		* @param GLenum the shader type
		* @return the compilation status
		*/
		const GLuint checkCompilation(const GLuint, const GLenum) const;

		/**
		* Checks the program for linkage errors
		*
		* @return the linkage status
		*/
		const GLuint checkLinkage() const;

		void insertUniform(const char*);

	public:

		ShaderProgram();
		ShaderProgram(const char*, const char*, bool isShadowShader);
		ShaderProgram(std::ifstream*, std::ifstream*, bool isShadowShader);
		~ShaderProgram();

		////////////////
		// Assignment //
		////////////////

		const ShaderProgram& operator= (const ShaderProgram&);

		///////////////
		// Functions //
		///////////////

		/**
		* Adds a new shader to the shader program
		*
		* @param char* the shader code
		* @param GLenum the shader type
		* @return the shader ID
		*/
		const GLuint addShader(const char*, const GLenum);

		const GLuint getUniform(std::string) const;

		const int getBinding(std::string) const;

		GLuint getShaderId() { return ProgramId; };

		void use() const;

	};

}