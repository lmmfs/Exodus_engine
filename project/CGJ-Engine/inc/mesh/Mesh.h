#pragma once
#include <vector>
#include "Drawable.h"
#include "BufferObject.h"
#include "maths/Matrix.h"
#include "shader/ShaderProgram.h"

namespace engine {

	class ShaderProgram;

	/**
	* Represents a Shader Vertex
	*
	*/
	class Vertex
	{
	public:
		GLfloat XYZW[4];

		const Vertex& operator+ (const Vertex& v) const {
			Vertex v1;
			for (int i = 0; i < 4; ++i) {
				v1.XYZW[i] = XYZW[i] + v.XYZW[i];
			}
			return (*new Vertex(v1));
		}

		const Vertex& operator* (const float scalar) const {
			Vertex v1;
			for (int i = 0; i < 4; ++i) {
				v1.XYZW[i] = XYZW[i] * scalar;
			}
			return (*new Vertex(v1));
		}

		const Vertex& operator*= (const float scalar) {
			for (int i = 0; i < 4; ++i) {
				XYZW[i] *= scalar;
			}
			return (*this);
		}
	};

	/**
	* Represents a Shader Texture Coordinate
	*
	*/
	class TexCoord
	{
	public:
		GLfloat UV[2];

		const TexCoord& operator+ (const TexCoord& v) const {
			TexCoord v1;
			for (int i = 0; i < 2; ++i) {
				v1.UV[i] = UV[i] + v.UV[i];
			}
			return (*new TexCoord(v1));
		}

		const TexCoord& operator* (const float scalar) const {
			TexCoord v1;
			for (int i = 0; i < 2; ++i) {
				v1.UV[i] = UV[i] * scalar;
			}
			return (*new TexCoord(v1));
		}

		const TexCoord& operator*= (const float scalar) {
			for (int i = 0; i < 2; ++i) {
				UV[i] *= scalar;
			}
			return (*this);
		}
	};

	/**
	* Represents a Mesh
	*
	*/
	class Mesh : public Drawable, BufferObject {

	protected:

		std::vector<Vertex> vertices;

		std::vector<TexCoord> texCoords;

		std::vector<Vertex> normals;

		std::vector<int> vertexIdx, texCoordIdx, normalIdx;

		std::vector<Vertex> vertexData, normalData;

		std::vector<TexCoord> texCoordData;

		Vertex color = { 1.0f, 1.0f, 1.0f, 1.0f };

		bool TexcoordsLoaded = false, NormalsLoaded = false;

		void parseVertex(std::stringstream&);

		void parseTexCoord(std::stringstream&);

		void parseNormal(std::stringstream&);

		void parseFace(std::stringstream&);

		void parseLine(std::stringstream&);

		void loadMeshData(const char*);

		void processMeshData();

		void freeMeshData();

		void setVertexAttrib(const GLuint);

		void setTexCoordAttrib(const GLuint);

		void setNormalAttrib(const GLuint);

	protected:

		GLuint VaoId = 0, IndexVboId = 0, VboId = 0, TexCoordVboId = 0, NormalVboId = 0;

		static int indexAttrib, vertexAttrib, texcoordAttrib, normalAttrib;

		Matrix4 modelMatrix = MatrixFactory::Identity4();

		// The Scale in X Y and Z of this object
		float xScale = 1, yScale = 1, zScale = 1;

		virtual const Matrix4 getModelMatrix() const;

	public:

		/**
		* Gets the vertices of this object
		*
		* @return vertices The array of vertices
		*/
		virtual const std::vector<Vertex> getVertices() const;

	public:

		Mesh();
		~Mesh();

		const bool operator == (const Mesh&) const;

		const bool operator != (const Mesh&) const;

		static Mesh* parseMesh(const char*, ShaderProgram*);

		const Vertex getColor() const;

		/**
		* Scales the object
		*
		* @param x The scale in X
		* @param y The scale in Y
		*/
		void scale(const float, const float, const float = 1);

		/**
		* Rotates the object
		*
		* @param degrees The angle to rotate in degrees
		*/
		void rotate(const float, const char = 'z');

		/**
		* Translates the object
		*
		* @param x The translation in X
		* @param y The translation in Y
		*/
		void translate(const float, const float, const float = 0);

		Mesh* inColor(Vertex);

		std::vector<float> getBoundingCoords() const;

		////////////////////////////////////////////////////////
		// BufferObject - @see BufferObject.h for definitions //
		////////////////////////////////////////////////////////

	protected:

		void createBufferObject() override;

		void destroyBufferObject() const override;

		////////////////////////////////////////////////
		// Drawable - @see Drawable.h for definitions //
		////////////////////////////////////////////////

	public:

		void draw() override;

	};

}