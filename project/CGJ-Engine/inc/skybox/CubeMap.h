#pragma once

#include <vector>
#include <string>
#include "mesh/Mesh.h"
#include <GL/glew.h>
#include <assert.h>
#include "ImageLoader.h"
#include <iostream>

namespace engine {
	class Cubemap
	{
	public:
		Cubemap();
		Cubemap(std::vector<std::string> faces, Mesh* mesh);

		~Cubemap();

		void Bind(unsigned int unit);

		void drawCubemap();

		static Cubemap* loadCubemap(std::vector<std::string> faces, Mesh* mesh);

	private:
		GLuint 	m_cubemap_id = 0;

		Mesh* mesh;

	};


}