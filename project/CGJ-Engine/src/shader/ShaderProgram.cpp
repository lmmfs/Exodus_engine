#include "Shader/ShaderProgram.h"
#include "Utils.h"

namespace engine {

	/**
	* For all implementations in this file, @see ShaderProgram.h for details
	*/

	ShaderProgram::ShaderProgram() {
	}

	ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader, bool isShadow) {
		this->isShadowShader = isShadow;
		if (!this->isShadowShader)
			Init(vertexShader, fragmentShader);
		else
			InitShadow(vertexShader, fragmentShader);
	}

	ShaderProgram::ShaderProgram(std::ifstream* vertexShaderFile, std::ifstream* fragmentShaderFile, bool isShadow) {
		const GLchar* VertexShader = IO::readLinesFromFile(vertexShaderFile);
		const GLchar* FragmentShader = IO::readLinesFromFile(fragmentShaderFile);
		this->isShadowShader = isShadow;
		if (!this->isShadowShader)
			Init(VertexShader, FragmentShader);
		else
			InitShadow(VertexShader, FragmentShader);
	}

	const char* shaderType(const GLenum shaderType) {
		switch (shaderType) {
		case GL_VERTEX_SHADER: return "Vertex Shader";
		case GL_FRAGMENT_SHADER: return "Fragment Shader";
		default: return "Unknown shader type";
		}
	}

	const GLuint ShaderProgram::checkCompilation(const GLuint shader_id, const GLenum type) const {
		GLint compiled;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
			GLchar* const log = new char[length];
			glGetShaderInfoLog(shader_id, length, &length, log);
			std::cerr << "[" << shaderType(type) << "] " << std::endl << log;
			delete[] log;
		}
		return compiled;
	}

	const GLuint ShaderProgram::checkLinkage() const {
		GLint linked;
		glGetProgramiv(ProgramId, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			GLint length;
			glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &length);
			GLchar* const log = new char[length];
			glGetProgramInfoLog(ProgramId, length, &length, log);
			std::cerr << "[LINK] " << std::endl << log << std::endl;
			delete[] log;
		}
		return linked;
	}

	const GLuint ShaderProgram::addShader(const char* shader, const GLenum type) {

		const GLuint shaderId = glCreateShader(type);
		glShaderSource(shaderId, 1, &shader, 0);
		glCompileShader(shaderId);
		checkCompilation(shaderId, type);
		glAttachShader(ProgramId, shaderId);
		return shaderId;

	}

	void ShaderProgram::insertUniform(const char* name) {
		uniforms.insert(std::pair<std::string, GLuint>(std::string(name), glGetUniformLocation(ProgramId, name)));
	}

	void ShaderProgram::Init(const char* vertexShader, const char* fragmentShader) {

		ProgramId = glCreateProgram();

		const GLuint VertexShaderId = addShader(vertexShader, GL_VERTEX_SHADER);
		const GLuint FragmentShaderId = addShader(fragmentShader, GL_FRAGMENT_SHADER);

		glBindAttribLocation(ProgramId, bindings.at("VERTICES"), "in_Position");
		glBindAttribLocation(ProgramId, bindings.at("TEX_COORDS"), "in_TexCoord");
		glBindAttribLocation(ProgramId, bindings.at("NORMALS"), "in_Normal");

		glLinkProgram(ProgramId);
		checkLinkage();

		insertUniform("Color");
		insertUniform("ModelMatrix");
		insertUniform("viewPos");
		insertUniform("lightSpaceMatrix");
		insertUniform("lightPos");
		insertUniform("shadowMap");

		insertUniform("ourSampler");
		insertUniform("material");
		insertUniform("powerSlide");

		glUniformBlockBinding(ProgramId, glGetUniformBlockIndex(ProgramId, "SharedMatrices"), bindings.at("UBO_BP"));


		glDetachShader(ProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);

	}

	void ShaderProgram::InitShadow(const char* vertexShader, const char* fragmentShader) {

		ProgramId = glCreateProgram();

		const GLuint VertexShaderId = addShader(vertexShader, GL_VERTEX_SHADER);
		const GLuint FragmentShaderId = addShader(fragmentShader, GL_FRAGMENT_SHADER);

		glBindAttribLocation(ProgramId, bindings.at("VERTICES"), "in_Position");

		glLinkProgram(ProgramId);
		checkLinkage();

		insertUniform("model");
		insertUniform("lightSpaceMatrix");
		insertUniform("shadowMap");

		glDetachShader(ProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);

	}

	void ShaderProgram::InitSkyBox(const char* vertexShader, const char* fragmentShader)
	{
		ProgramId = glCreateProgram();

		const GLuint VertexShaderId = addShader(vertexShader, GL_VERTEX_SHADER);
		const GLuint FragmentShaderId = addShader(fragmentShader, GL_FRAGMENT_SHADER);

		glBindAttribLocation(ProgramId, bindings.at("VERTICES"), "in_Position");

		glLinkProgram(ProgramId);
		checkLinkage();

		insertUniform("model");
		
		glUniformBlockBinding(ProgramId, glGetUniformBlockIndex(ProgramId, "SharedMatrices"), bindings.at("UBO_BP"));


		glDetachShader(ProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
		glDetachShader(ProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);
	}

	ShaderProgram::~ShaderProgram() {
		glUseProgram(0);
		glDeleteProgram(ProgramId);
	}

	const ShaderProgram& ShaderProgram::operator= (const ShaderProgram& shaderProgram) {
		ProgramId = shaderProgram.ProgramId;
		uniforms = shaderProgram.uniforms;
		return (*this);
	}

	const GLuint ShaderProgram::getUniform(std::string name) const {
		return uniforms.at(name);
	}

	const int ShaderProgram::getBinding(std::string name) const {
		return bindings.at(name);
	}

	void ShaderProgram::use() const {
		glUseProgram(ProgramId);
	}

}