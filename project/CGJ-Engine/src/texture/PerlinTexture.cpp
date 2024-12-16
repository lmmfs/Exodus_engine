#include "textures/PerlinTexture.h"
#include <cassert>
#include <iostream>

#define STB_PERLIN_IMPLEMENTATION
#include "PerlinNoise.h"

GLubyte imageData[imageWidth][imageWidth][4];

namespace engine {
	PerlinTexture::PerlinTexture()
	{
		glGenTextures(1, &m_texture_id);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
		
		createImage();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
		
	}
	
	void PerlinTexture::createImage() {
		bool mid = false;
		for (int row = 0; row < imageWidth; row++) {
			for (int col = 0; col < imageWidth; col++) {
				float dx = (float) row / imageWidth;
				float dy = (float) col / imageWidth;
				float noise = stb_perlin_turbulence_noise3(dx, dy, 3.2f, 2.0f, 0.5f, 6);
				
				int colorValue = (int)(noise * 255);

				imageData[row][col][0] = colorValue;
				imageData[row][col][1] = colorValue;
				imageData[row][col][2] = colorValue;
				imageData[row][col][2] = 255;
			}
		}
		
	}

	PerlinTexture::~PerlinTexture()
	{
		glDeleteTextures(1, &m_texture_id);
	}

	PerlinTexture* PerlinTexture::parsePerlin()
	{
		PerlinTexture* t = new PerlinTexture();
		return t;
	}

	void PerlinTexture::Bind(unsigned int unit)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture_id);
	}

	void PerlinTexture::testPerlin(float x, float y)
	{
		std::cout << "( " << x << " , " << y << " )"<< std::endl;
		float noise = stb_perlin_noise3(x, y, 4.0f, 0, 0, 0);
		noise = (noise + 1) / 2;
		int colorValue = (int)(noise * 255);
		std::cout << noise << std::endl;
		std::cout << colorValue << std::endl;
	}


}