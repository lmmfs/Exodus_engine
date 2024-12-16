#pragma once
#include <GL/glew.h>

#define imageWidth 256

namespace engine {
	class PerlinTexture
	{
	public:
		PerlinTexture();
		~PerlinTexture();

		static PerlinTexture* parsePerlin();

		void Bind(unsigned int unit);
		void testPerlin(float x, float y);

	private:
		GLuint 	m_texture_id = 0;
		void createImage();
		
		
	};

	
}