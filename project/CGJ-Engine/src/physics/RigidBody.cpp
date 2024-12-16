#include "physics/RigidBody.h"
#include "physics/Physics.h"
#include "Utils.h"
#include "GLFW/glfw3.h"

namespace engine {
	
	const float RigidBody::getMass() {
		return mass;
	}

	void RigidBody::setMass(const float mass) {
		this->mass = mass;
	}

	const float RigidBody::getBounciness() {
		return bounciness;
	}

	void RigidBody::setBounciness(const float bounciness) {
		this->bounciness = bounciness;
	}

	const Vector3 RigidBody::getSpeed() {
		return speed;
	}

	void RigidBody::setSpeed(const Vector3 speed) {
		this->speed = speed;
	}

	void RigidBody::addForce(Vector3 force) {
		this->forces.push_back(force);
	}

	void RigidBody::update() {
		if (mass > 0.0f) {
			float time = (float)glfwGetTime();
			float elapsed_time = time - lastTime;
			lastTime = time;
			if (elapsed_time > 0.03f) {
				// Simple trick used in debug
				return;
			}
			forces.push_back(Physics::getInstance()->getGravityVector());
			for (Vector3 force : forces) {
				this->speed += force * this->mass * elapsed_time;
			}
			forces.clear();

			/** /
			
			if (dynamic_cast<SphericalRigidBody*>(this)) {
				Quaternion rotateAroundZ = Quaternion::fromAngleAxis(-speed.x / 2.0f, Vector3(0.0f, 0.0f, 1.0f));
				Quaternion rotateAroundX = Quaternion::fromAngleAxis(-speed.z / 2.0f, Vector3(1.0f, 0.0f, 0.0f));
				this->node->setRotation(*this->node->getRotation() * rotateAroundZ * rotateAroundX);
			}

			/**/

			node->setPosition(*node->getPosition() + (getSpeed() * elapsed_time));
			previousSpeed = speed;
		}
	}

	void RigidBody::onCollisionEnter(Collider* collider, Collider* other, Vector3 collisionPoint) {
		if (mass > 0.0f && other->getSceneNode()->getRigidBody()) {
			if (other->getSceneNode()->getPosition()->y > getSceneNode()->getPosition()->y && other->getSceneNode()->getRigidBody()->getMass() == 0.0f) {
				this->node->setPosition(Vector3(node->getPosition()->x, other->getSceneNode()->getPosition()->y - other->getHeight() / 2 - collider->getHeight() / 2, node->getPosition()->z));
			}
			Vector3 newSpeed = other->getSceneNode()->getRigidBody()->getSpeed();
			newSpeed.x *= newSpeed.x;
			newSpeed.y *= newSpeed.y;
			newSpeed.z *= newSpeed.z;
			addForce(bounciness * -newSpeed * (other->getSceneNode()->getRigidBody()->getMass() / mass));
			float x = speed.x / (1.0f + pow(10.0f, -3.0f));
			float z = speed.z / (1.0f + pow(10.0f, -3.0f));
			this->speed = Vector3(x, 0, z);
		}
	}

	void RigidBody::onCollisionExit(Collider* collider, Collider* other) {
	}

	void SphericalRigidBody::onCollisionEnter(Collider* collider, Collider* other, Vector3 collisionPoint) {
		if (mass > 0.0f && other->getSceneNode()->getRigidBody()) {
			if (other->getSceneNode()->getPosition()->y > getSceneNode()->getPosition()->y) {
				this->node->setPosition(Vector3(node->getPosition()->x, other->getSceneNode()->getPosition()->y - other->getHeight() / 2 - collider->getHeight() / 2, node->getPosition()->z));
			}
			Vector3 newSpeed = other->getSceneNode()->getRigidBody()->getSpeed();
			newSpeed.x *= newSpeed.x;
			newSpeed.y *= newSpeed.y;
			newSpeed.z *= newSpeed.z;
			addForce(bounciness * newSpeed * (other->getSceneNode()->getRigidBody()->getMass() / mass));
			float x = (speed.x == 0 ? static_cast <float> (rand()) / static_cast <float> (RAND_MAX) : speed.x) / (1.0f + pow(10.0f, -3.0f));
			float z = (speed.z == 0 ? static_cast <float> (rand()) / static_cast <float> (RAND_MAX) : speed.z) / (1.0f + pow(10.0f, -3.0f));
			this->speed = Vector3(x, 0, z);
		}
	}

}