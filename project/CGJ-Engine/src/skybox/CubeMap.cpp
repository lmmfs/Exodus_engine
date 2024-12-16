#include "skybox/CubeMap.h"

namespace engine {

	Cubemap::Cubemap()
	{
        this->mesh = nullptr;
	}

	Cubemap::Cubemap(std::vector<std::string> faces, Mesh* mesh)
	{
        this->mesh = mesh;

        glGenTextures(1, &m_cubemap_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap_id);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 4);
            if (data)
            {
                glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	Cubemap::~Cubemap()
	{
	}

	void Cubemap::Bind(unsigned int unit)
	{
		assert(unit >= 0 && unit <= 31);
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap_id);
	}

    void Cubemap::drawCubemap()
    {
        Bind(0);
        mesh->draw();
    }

    Cubemap* Cubemap::loadCubemap(std::vector<std::string> faces, Mesh* mesh)
	{
		Cubemap* c = new Cubemap(faces, mesh);
		return c;
	}

    
}