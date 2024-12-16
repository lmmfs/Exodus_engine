#include "physics/Collider.h"
#include "physics/Physics.h"

namespace engine {

	const std::vector<Vertex> Collider::getVertices() const {
		std::vector<Vertex> verticesRes = Mesh::getVertices();
		for (int i = 0; i < verticesRes.size(); ++i) {
			Vector3 v(verticesRes[i].XYZW[0], verticesRes[i].XYZW[1], verticesRes[i].XYZW[2]);
			v = *node->getWorldMatrix() * v;
			verticesRes[i] = { v.x, v.y, v.z, 0.0f };
		}
		return verticesRes;
	}

	std::vector<CollisionListener*> Collider::getListeners() const {
		return listeners;
	}

	void Collider::addListener(CollisionListener* listener) {
		listeners.push_back(listener);
	}

	const float Collider::getHeight() const {
		std::vector<float> bounds = getBoundingCoords();
		return bounds[2] - bounds[3];
	}

	const float Collider::getWidth() const {
		std::vector<float> bounds = getBoundingCoords();
		return bounds[0] - bounds[1];
	}

	void Collider::update() {
		// DETECT COLLISIONS
		if (Physics::getInstance()->showColliders()) {
			glUniform4fv(node->getShaderProgram()->getUniform("Color"), 1, getColor().XYZW);
			glUniformMatrix4fv(node->getShaderProgram()->getUniform("ModelMatrix"), 1, GL_FALSE, node->getWorldMatrix()->elements);
			draw();
		}

		std::vector<Collider*> colliders = Physics::getColliders({ this });
		std::vector<float> bounds = getBoundingCoords();
		for (Collider* collider : colliders) {
			bool vertexInside = false;
			std::vector<Vertex> vertices = collider->getVertices();
			for (int i = 0; i < vertices.size(); i += 3) {
				int i1 = i + 1, i2 = i + 2;
				Vertex center = (vertices[i] + vertices[i1] + vertices[i2]) * 0.33;
				Vertex collision;
				bool collided = false;
				if (isInside(vertices[i], bounds)) {
					collision = vertices[i];
					collided = true;
				}
				else if (isInside(vertices[i1], bounds)) {
					collision = vertices[i1];
					collided = true;
				}
				else if (isInside(vertices[i2], bounds)) {
					collision = vertices[i2];
					collided = true;
				}
				else if (isInside(center, bounds)) {
					collision = center;
					collided = true;
				}

				if (collided) {
					inCollision.push_back(collider);
					collider->inCollision.push_back(this);
					for (CollisionListener* listener : getListeners()) {
						listener->onCollisionEnter(this, collider, Vector3(collision.XYZW[0], collision.XYZW[1], collision.XYZW[2]));
					}
					for (CollisionListener* listener : collider->getListeners()) {
						listener->onCollisionEnter(collider, this, Vector3(collision.XYZW[0], collision.XYZW[1], collision.XYZW[2]));
					}
					vertexInside = true;
					//break;
				}
			}
			if (!vertexInside && std::find(inCollision.begin(), inCollision.end(), collider) != inCollision.end()) {
				inCollision.erase(std::find(inCollision.begin(), inCollision.end(), collider));
				collider->inCollision.erase(std::find(collider->inCollision.begin(), collider->inCollision.end(), this));
				for (CollisionListener* listener : getListeners()) {
					listener->onCollisionExit(this, collider);
				}
				for (CollisionListener* listener : collider->getListeners()) {
					listener->onCollisionExit(collider, this);
				}
			}
		}
	}

	BoxCollider::BoxCollider(Mesh* mesh) {

		this->color = { 1.0f, 1.0f, 1.0f, 0.2f };

		std::vector<float> bounds = mesh->getBoundingCoords();

		// 0: maxX
		// 1: minX
		// 2: maxY
		// 3: minY
		// 4: maxZ
		// 5: minZ

		this->vertexData.push_back({ bounds[0], bounds[3], bounds[5] });
		this->vertexData.push_back({ bounds[0], bounds[2], bounds[4] });
		this->vertexData.push_back({ bounds[0], bounds[3], bounds[4] });
		this->vertexData.push_back({ bounds[1], bounds[3], bounds[5] });
		this->vertexData.push_back({ bounds[0], bounds[2], bounds[5] });
		this->vertexData.push_back({ bounds[1], bounds[2], bounds[4] });
		this->vertexData.push_back({ bounds[1], bounds[3], bounds[4] });
		this->vertexData.push_back({ bounds[1], bounds[2], bounds[5] });

		this->vertexIdx.push_back(4); this->vertexIdx.push_back(7); this->vertexIdx.push_back(6);
		this->vertexIdx.push_back(6); this->vertexIdx.push_back(8); this->vertexIdx.push_back(4);
		this->vertexIdx.push_back(7); this->vertexIdx.push_back(3); this->vertexIdx.push_back(2);
		this->vertexIdx.push_back(2); this->vertexIdx.push_back(6); this->vertexIdx.push_back(7);
		this->vertexIdx.push_back(3); this->vertexIdx.push_back(1); this->vertexIdx.push_back(5);
		this->vertexIdx.push_back(5); this->vertexIdx.push_back(2); this->vertexIdx.push_back(3);
		this->vertexIdx.push_back(6); this->vertexIdx.push_back(2); this->vertexIdx.push_back(5);
		this->vertexIdx.push_back(5); this->vertexIdx.push_back(8); this->vertexIdx.push_back(6);
		this->vertexIdx.push_back(4); this->vertexIdx.push_back(1); this->vertexIdx.push_back(3);
		this->vertexIdx.push_back(3); this->vertexIdx.push_back(7); this->vertexIdx.push_back(4);
		this->vertexIdx.push_back(8); this->vertexIdx.push_back(5); this->vertexIdx.push_back(1);
		this->vertexIdx.push_back(1); this->vertexIdx.push_back(4); this->vertexIdx.push_back(8);

		this->processMeshData();

		this->createBufferObject();

	}

	bool BoxCollider::isInside(Vertex v, std::vector<float> bounds) const {
		return (v.XYZW[0] <= bounds[0] && v.XYZW[0] >= bounds[1]) &&
			(v.XYZW[1] <= bounds[2] && v.XYZW[1] >= bounds[3]) &&
			(v.XYZW[2] <= bounds[4] && v.XYZW[2] >= bounds[5]);
	}

	MeshCollider::MeshCollider(Mesh* mesh) {
		this->color = { 1.0f, 1.0f, 1.0f, 0.2f };
		this->vertices = mesh->getVertices();

		createBufferObject();
	}

	bool MeshCollider::isInside(Vertex v, std::vector<float> bounds) const {

		// TODO: not yet implemented

		return false;

	}

}