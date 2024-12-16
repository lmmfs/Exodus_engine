#pragma once

#include <string>
#include <GL/glew.h>

namespace engine {
	class Texture
	{
	public:
		Texture();
		Texture(const std::string fileName);

		~Texture();
		void Bind(unsigned int unit);

		static Texture* parseTexture(const std::string fileName);

	private:
		GLuint 	m_texture_id = 0;
	};

	
}