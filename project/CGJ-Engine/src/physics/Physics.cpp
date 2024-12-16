#include "physics/Physics.h"

namespace engine {

	Physics* Physics::instance;

	Physics* Physics::getInstance() {
		if (instance == nullptr) {
			instance = new Physics();
		}
		return instance;
	}

	RigidBody* Physics::newRigidBody(const float mass, const float bounciness) {
		return getInstance()->createRigidBody(mass, bounciness);
	}

	RigidBody* Physics::newSphericalRigidBody(const float mass, const float bounciness) {
		return getInstance()->createSphericalRigidBody(mass, bounciness);
	}

	Collider* Physics::newBoxCollider(Mesh* mesh) {
		BoxCollider* collider = getInstance()->createBoxCollider(mesh);
		return collider;
	}

	Collider* Physics::newMeshCollider(Mesh* mesh) {
		return getInstance()->createMeshCollider(mesh);
	}

	std::vector<Collider*> Physics::getColliders(std::vector<Collider*> ignores) {
		std::vector<Collider*> colliders;
		for (Updatable* component : getInstance()->components) {
			Collider* collider = dynamic_cast<Collider*>(component);
			if (collider && std::find(ignores.begin(), ignores.end(), collider) == ignores.end()) {
				colliders.push_back(collider);
			}
		}
		return colliders;
	}

	Physics::Physics() {
		setGravity(EARTH_GRAVITY);
	}

	const float Physics::getGravity() {
		return gravity;
	}

	void Physics::setGravity(const float gravity) {
		this->gravity = gravity;
		this->gravityVector = Vector3(0.0f, -gravity, 0.0f);
	}

	const Vector3 Physics::getGravityVector() {
		return this->gravityVector;
	}

	RigidBody* Physics::createRigidBody(const float mass, const float bounciness) {
		RigidBody* body = new RigidBody();
		body->setMass(mass);
		body->setBounciness(bounciness);
		components.push_back(body);
		return body;
	}

	SphericalRigidBody* Physics::createSphericalRigidBody(const float mass, const float bounciness) {
		SphericalRigidBody* body = new SphericalRigidBody();
		body->setMass(mass);
		body->setBounciness(bounciness);
		components.push_back(body);
		return body;
	}

	BoxCollider* Physics::createBoxCollider(Mesh* mesh) {
		BoxCollider* collider = new BoxCollider(mesh);
		components.push_back(collider);
		return collider;
	}

	MeshCollider* Physics::createMeshCollider(Mesh* mesh) {
		MeshCollider* collider = new MeshCollider(mesh);
		components.push_back(collider);
		return collider;
	}

	void Physics::toggleShowColliders() {
		drawColliders = !drawColliders;
	}

	bool Physics::showColliders() const {
		return drawColliders;
	}

	void Physics::update() {
		for (Updatable* component : components) {
			component->update();
		}
	}

}