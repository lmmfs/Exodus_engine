#include "scene/SceneNode.h"
#include "physics/Collider.h"
#include "physics/CollisionListener.h"
#include "physics/RigidBody.h"

namespace engine {

	SceneNode::SceneNode() {
		this->shaderProgram = nullptr;
		this->shadowShaderProgram = nullptr;
		this->parent = nullptr;
		this->mesh = nullptr;
		this->shadowMesh = nullptr;
		this->worldMatrix = new Matrix4(1);
		this->localMatrix = new Matrix4(1);
		this->scale = new Vector3(1.0f);
		this->position = new Vector3();
		this->rotation = new Quaternion();
		this->texture = nullptr;
		this->perlinTexture = nullptr;
		this->material = nullptr;
	}

	const SceneNode* SceneNode::operator= (SceneNode* node) {
		this->localMatrix = node->getMatrix();
		this->worldMatrix = node->getWorldMatrix();
		this->scale = node->getScale();
		this->position = node->getPosition();
		this->rotation = node->getRotation();
		this->mesh = node->getMesh();
		this->shaderProgram = node->getShaderProgram();
		this->shadowShaderProgram = node->getShadowShaderProgram();
		this->parent = node->getParent();
		this->children = node->getChildren();
		this->texture = node->getTexture();
		this->perlinTexture = node->getPerlinTexture();
		this->material = node->getMaterial();
		return this;
	}

	Matrix4* SceneNode::getMatrix() const {
		return new Matrix4(*this->localMatrix *
						   MatrixFactory::Translate(*position) *
						   (Matrix4)*rotation *
						   MatrixFactory::Scale(*scale));
	}

	Matrix4* SceneNode::getLocalMatrix() const {
		return this->localMatrix;
	}

	Vector3* SceneNode::getScale() const {
		return this->scale;
	}

	Vector3* SceneNode::getPosition() const {
		return this->position;
	}

	Quaternion* SceneNode::getRotation() const {
		return this->rotation;
	}

	Matrix4* SceneNode::getWorldMatrix() const {
		return this->worldMatrix;
	}

	void SceneNode::setLocalMatrix(Matrix4 matrix) {
		*this->localMatrix = matrix;
	}

	void SceneNode::setScale(Vector3 scale) {
		*this->scale = scale;
	}

	void SceneNode::setPosition(Vector3 translate) {
		*this->position = translate;
	}

	void SceneNode::setRotation(Quaternion rotate) {
		*this->rotation = rotate;
	}

	void SceneNode::setWorldMatrix(Matrix4* matrix) {
		this->worldMatrix = matrix;
	}

	void SceneNode::updateWorldMatrix() {
		if (this->parent->getWorldMatrix() != nullptr) {
			*this->worldMatrix = *this->parent->getWorldMatrix() * *this->getMatrix();
		}
		else {
			this->worldMatrix = this->getMatrix();
		}
	}

	Mesh* SceneNode::getMesh() const {
		return mesh != nullptr ? mesh : parent->getMesh();
	}

	void SceneNode::setMesh(Mesh* mesh) {
		this->mesh = mesh;
	}

	void SceneNode::setShadowMesh(Mesh* mesh) {
		this->shadowMesh = mesh;
	}

	Texture* SceneNode::getTexture() const
	{
		return texture;
	}

	void SceneNode::setTexture(Texture* texture)
	{
		this->texture = texture;
	}

	PerlinTexture* SceneNode::getPerlinTexture() const
	{
		return perlinTexture;
	}

	void SceneNode::setPerlinTexture(PerlinTexture* texture)
	{
		this->perlinTexture = texture;
	}

	Material* SceneNode::getMaterial() const
	{
		return material;
	}

	void SceneNode::setMaterial(Material* material)
	{
		this->material = material;
	}

	ShaderProgram* SceneNode::getShaderProgram() const {
		return shaderProgram != nullptr ? shaderProgram : parent->getShaderProgram();
	}

	ShaderProgram* SceneNode::getShadowShaderProgram() const {
		return shadowShaderProgram != nullptr ? shadowShaderProgram : parent->getShadowShaderProgram();
	}

	void SceneNode::setShaderProgram(ShaderProgram* shaderProgram) {
		this->shaderProgram = shaderProgram;
	}

	void SceneNode::setShadowShaderProgram(ShaderProgram* shadow) {
		this->shadowShaderProgram = shadow;
	}

	SceneNode* SceneNode::getParent() const {
		return this->parent;
	}

	void SceneNode::setParent(SceneNode* node) {
		this->parent = node;
	}

	SceneNode* SceneNode::createNode() {
		SceneNode* node = new SceneNode();
		node->setParent(this);
		children.push_back(node);
		return node;
	}

	std::vector<SceneNode*> SceneNode::getChildren() const {
		return children;
	}

	void SceneNode::addComponent(SceneNodeComponent* component) {
		for (SceneNodeComponent* comp : components) {
			
			CollisionListener* cListener = dynamic_cast<CollisionListener*>(comp);
			Collider* col = dynamic_cast<Collider*>(component);

			if (cListener && col) {
				col->addListener(cListener);
			}
			
			cListener = dynamic_cast<CollisionListener*>(component);
			col = dynamic_cast<Collider*>(comp);

			if (cListener && col) {
				col->addListener(cListener);
			}

		}
		components.push_back(component);
		component->setSceneNode(this);
	}

	RigidBody* SceneNode::getRigidBody() const {
		for (SceneNodeComponent* component : components) {
			if (dynamic_cast<RigidBody*>(component)) {
				return dynamic_cast<RigidBody*>(component);
			}
		}
		return nullptr;
	}

	void SceneNode::addForce(Vector3 force) {
		RigidBody* body = getRigidBody();

		if (body) {
			body->addForce(force);
		}
			
	}

	void SceneNode::draw() {

		getShaderProgram()->use();

		if (texture != nullptr) {
			glUniform1i(glGetUniformLocation(getShaderProgram()->getShaderId(), "ourSampler"), 1);
			getTexture()->Bind(1);
		}
		if (perlinTexture != nullptr) {
			glUniform1i(glGetUniformLocation(getShaderProgram()->getShaderId(), "ourSampler"), 1);
			getPerlinTexture()->Bind(1);
		}

		if (material != nullptr) {
			glUniform1f(glGetUniformLocation(getShaderProgram()->getShaderId(), "material.ambientStrength"), getMaterial()->getAmbientStrength());
			glUniform1f(glGetUniformLocation(getShaderProgram()->getShaderId(), "material.specularStrength"), getMaterial()->getSpecularStrength());
			glUniform1f(glGetUniformLocation(getShaderProgram()->getShaderId(), "material.shininess"), getMaterial()->getShininess());
			glUniform1f(glGetUniformLocation(getShaderProgram()->getShaderId(), "material.transparency"), getMaterial()->getTransparency());
			glUniform1i(glGetUniformLocation(getShaderProgram()->getShaderId(), "material.type"), getMaterial()->getMaterialType());
		}

		if (mesh != nullptr) {
			glUniform4fv(getShaderProgram()->getUniform("Color"), 1, getMesh()->getColor().XYZW);
			glUniformMatrix4fv(getShaderProgram()->getUniform("ModelMatrix"), 1, GL_FALSE, getWorldMatrix()->elements);
			mesh->draw();
		}
		for (SceneNode* node : children) {
			node->updateWorldMatrix();
			node->draw();
		}
	}

	void SceneNode::drawShadow(engine::ShaderProgram* shader) const {
		shader->use();

		if (shadowMesh != nullptr) {
			if (!material->isTranslucent()) {
				glUniformMatrix4fv(glGetUniformLocation(getShadowShaderProgram()->getShaderId(), "model"), 1, GL_FALSE, getWorldMatrix()->elements);
				shadowMesh->draw();
			}
		}
		for (SceneNode* node : children) {
			node->drawShadow(shader);
		}
	}

}