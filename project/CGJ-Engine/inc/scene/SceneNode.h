#pragma once

#include "scene/SceneNodeComponent.h"
#include "Drawable.h"
#include "maths/Matrix.h"
#include "maths/Vector.h"
#include "maths/Quaternion.h"
#include "mesh/Mesh.h"
#include "textures/Texture.h"
#include "textures/Material.h"
#include "textures/PerlinTexture.h"
#include <vector>

namespace engine {

	class Updatable;

	class RigidBody;

	class SceneNode : public Drawable {

	private:

		Matrix4* worldMatrix;

		Matrix4* localMatrix;

		Vector3* scale;

		Vector3* position;

		Quaternion* rotation;

		Mesh* mesh;
		Mesh* shadowMesh;

		Texture* texture;

		PerlinTexture* perlinTexture;

		Material* material;

		ShaderProgram* shaderProgram;
		ShaderProgram* shadowShaderProgram;

		SceneNode* parent;

		std::vector<SceneNode*> children;

		std::vector<SceneNodeComponent*> components;

		Matrix4* getMatrix() const;

	protected:

		void setParent(SceneNode*);

	public:

		SceneNode();

		const SceneNode* operator= (SceneNode*);

		Matrix4* getLocalMatrix() const;

		Vector3* getScale() const;

		Vector3* getPosition() const;

		Quaternion* getRotation() const;

		Matrix4* getWorldMatrix() const;

		void setLocalMatrix(Matrix4);

		void setScale(Vector3);

		void setPosition(Vector3);

		void setRotation(Quaternion);

		void setWorldMatrix(Matrix4*);

		void updateWorldMatrix();

		Mesh* getMesh() const;

		virtual void setMesh(Mesh*);
		void setShadowMesh(Mesh*);

		Texture* getTexture() const;

		void setTexture(Texture*);

		PerlinTexture* getPerlinTexture() const;

		void setPerlinTexture(PerlinTexture*);

		Material* getMaterial() const;

		void setMaterial(Material*);

		ShaderProgram* getShaderProgram() const;
		ShaderProgram* getShadowShaderProgram() const;

		void setShaderProgram(ShaderProgram*);
		void setShadowShaderProgram(ShaderProgram*);

		SceneNode* getParent() const;

		SceneNode* createNode();

		std::vector<SceneNode*> getChildren() const;

		void addComponent(SceneNodeComponent*);

		RigidBody* getRigidBody() const;

		void addForce(Vector3);

		////////////////////////////////////////////////
		// Drawable - @see Drawable.h for definitions //
		////////////////////////////////////////////////

	public:

		void draw() override;
		void drawShadow(engine::ShaderProgram* shader) const;

	};

}