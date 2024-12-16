#include "Mesh/Mesh.h"
#include "Utils.h"
#include <string>
#include <strstream>

namespace engine {

	int Mesh::vertexAttrib = -1, Mesh::texcoordAttrib = -1, Mesh::normalAttrib = -1;

	Mesh::Mesh() {
		this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	Mesh::~Mesh() {
		destroyBufferObject();
	}

	void Mesh::parseVertex(std::stringstream& sin)
	{
		Vertex v;
		sin >> v.XYZW[0] >> v.XYZW[2] >> v.XYZW[1];
		vertexData.push_back(v);
	}

	void Mesh::parseTexCoord(std::stringstream& sin)
	{
		TexCoord t;
		sin >> t.UV[0] >> t.UV[1];
		texCoordData.push_back(t);
	}

	void Mesh::parseNormal(std::stringstream& sin)
	{
		Vertex n;
		sin >> n.XYZW[0] >> n.XYZW[2] >> n.XYZW[1];
		normalData.push_back(n);
	}

	void Mesh::parseFace(std::stringstream& sin)
	{
		std::string token;
		if (normalData.empty() && texCoordData.empty())
		{
			for (int i = 0; i < 3; i++)
			{
				sin >> token;
				vertexIdx.push_back(std::stoi(token));
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				std::getline(sin, token, '/');
				if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
				std::getline(sin, token, '/');
				if (token.size() > 0) texCoordIdx.push_back(std::stoi(token));
				std::getline(sin, token, ' ');
				if (token.size() > 0) normalIdx.push_back(std::stoi(token));
			}
		}
	}

	void Mesh::parseLine(std::stringstream& sin)
	{
		std::string s;
		sin >> s;
		if (s.compare("v") == 0) parseVertex(sin);
		else if (s.compare("vt") == 0) parseTexCoord(sin);
		else if (s.compare("vn") == 0) parseNormal(sin);
		else if (s.compare("f") == 0) parseFace(sin);
	}

	void Mesh::loadMeshData(const char* filename)
	{
		std::vector<std::string> lines = IO::linesFromFile(filename);
		for (const std::string line : lines) {
			std::stringstream sline(line);
			parseLine(sline);
		}
		TexcoordsLoaded = (texCoordIdx.size() > 0);
		NormalsLoaded = (normalIdx.size() > 0);
	}

	void Mesh::processMeshData()
	{
		for (unsigned int i = 0; i < vertexIdx.size(); i++) {
			unsigned int vi = vertexIdx[i];
			Vertex v = vertexData[vi - 1];
			vertices.push_back(v);
			if (TexcoordsLoaded) {
				unsigned int ti = texCoordIdx[i];
				TexCoord t = texCoordData[ti - 1];
				texCoords.push_back(t);
			}
			if (NormalsLoaded) {
				unsigned int ni = normalIdx[i];
				Vertex n = normalData[ni - 1];
				normals.push_back(n);
			}
		}
	}

	void Mesh::freeMeshData()
	{
		vertexData.clear();
		texCoordData.clear();
		normalData.clear();
		vertexIdx.clear();
		texCoordIdx.clear();
		normalIdx.clear();
	}

	Mesh* Mesh::parseMesh(const char* wavefrontObjPath, ShaderProgram* shaderProgram) {

		Mesh* m = new Mesh();
		m->loadMeshData(wavefrontObjPath);
		m->processMeshData();
		m->freeMeshData();
		m->setVertexAttrib(shaderProgram->getBinding("VERTICES"));
		m->setTexCoordAttrib(shaderProgram->getBinding("TEX_COORDS"));
		m->setNormalAttrib(shaderProgram->getBinding("NORMALS"));
		m->createBufferObject();
		return m;

	}

	void Mesh::setVertexAttrib(const GLuint attrib) {
		this->vertexAttrib = attrib;
	}

	void Mesh::setTexCoordAttrib(const GLuint attrib) {
		this->texcoordAttrib = attrib;
	}

	void Mesh::setNormalAttrib(const GLuint attrib) {
		this->normalAttrib = attrib;
	}

	const bool Mesh::operator== (const Mesh& mesh) const {
		return this->vertices.data() == mesh.getVertices().data();
	}

	const bool Mesh::operator!= (const Mesh& mesh) const {
		return this->vertices.data() != mesh.getVertices().data();
	}

	const std::vector<Vertex> Mesh::getVertices() const {
		return vertices;
	}

	const Matrix4 Mesh::getModelMatrix() const {
		return modelMatrix;
	}

	const Vertex Mesh::getColor() const {
		return color;
	}

	void Mesh::createBufferObject() {
		glGenVertexArrays(1, &VaoId);
		glBindVertexArray(VaoId);

		glGenBuffers(1, &VboId);
		glBindBuffer(GL_ARRAY_BUFFER, VboId);
		{
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
			glEnableVertexAttribArray(Mesh::vertexAttrib);
			glVertexAttribPointer(Mesh::vertexAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}

		if (texcoordAttrib != -1 && TexcoordsLoaded) {

			glGenBuffers(1, &TexCoordVboId);
			glBindBuffer(GL_ARRAY_BUFFER, TexCoordVboId);
			{
				glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(TexCoord), &texCoords[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(texcoordAttrib);
				glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(TexCoord), 0);
			}
		}

		if (normalAttrib != -1 && NormalsLoaded) {

			glGenBuffers(1, &NormalVboId);
			glBindBuffer(GL_ARRAY_BUFFER, NormalVboId);
			{
				glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vertex), &normals[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(normalAttrib);
				glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			}
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::destroyBufferObject() const {
		glBindVertexArray(VaoId);
		glDisableVertexAttribArray(vertexAttrib);
		glDeleteBuffers(1, &VboId);
		if (texcoordAttrib != -1) {
			glDisableVertexAttribArray(texcoordAttrib);
			glDeleteBuffers(1, &TexCoordVboId);
		}
		if (normalAttrib != -1) {
			glDisableVertexAttribArray(normalAttrib);
			glDeleteBuffers(1, &NormalVboId);
		}
		glDeleteVertexArrays(1, &VaoId);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Mesh::draw() {
		glBindVertexArray(VaoId);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
		glBindVertexArray(0);
	}

	void Mesh::scale(const float x, const float y, const float z) {
		xScale = x;
		yScale = y;
		zScale = z;
		modelMatrix = MatrixFactory::Scale(x, y, z) * modelMatrix;
	}

	void Mesh::rotate(const float degrees, const char axis) {
		modelMatrix = MatrixFactory::Rotate(degrees, axis) * modelMatrix;
	}

	void Mesh::translate(const float x, const float y, const float z) {
		modelMatrix = MatrixFactory::Translate(x, y, z) * modelMatrix;
	}

	Mesh* Mesh::inColor(Vertex color) {
		Mesh* m = new Mesh(*this);
		m->color = color;
		return m;
	}

	std::vector<float> Mesh::getBoundingCoords() const {
		float constexpr inf = std::numeric_limits<float>::infinity();
		std::vector<float> bounds = { -inf, inf, -inf, inf, -inf, inf };
		for (Vertex v : getVertices()) {
			if (v.XYZW[0] > bounds[0]) {
				bounds[0] = v.XYZW[0];
			}
			if (v.XYZW[0] < bounds[1]) {
				bounds[1] = v.XYZW[0];
			}
			if (v.XYZW[1] > bounds[2]) {
				bounds[2] = v.XYZW[1];
			}
			if (v.XYZW[1] < bounds[3]) {
				bounds[3] = v.XYZW[1];
			}
			if (v.XYZW[2] > bounds[4]) {
				bounds[4] = v.XYZW[2];
			}
			if (v.XYZW[2] < bounds[5]) {
				bounds[5] = v.XYZW[2];
			}
		}
		return bounds;
	}

}