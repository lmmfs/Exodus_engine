#pragma once

#include "Updatable.h"
#include "scene/SceneNodeComponent.h"
#include "physics/CollisionListener.h"
#include "maths/Vector.h"

namespace engine {

	class RigidBody : public Updatable, public SceneNodeComponent, public CollisionListener {

	protected:

		bool grounded = false;

		float mass = 0;

		Vector3 speed;

		Vector3 previousSpeed;

		std::vector<Vector3> forces;

		float lastTime = 0;

		float bounciness = 1.0f;

	public:

		const float getMass();

		void setMass(const float);

		const float getBounciness();

		void setBounciness(const float);

		const Vector3 getSpeed();

		void setSpeed(const Vector3);

		void addForce(const Vector3);
		
		virtual void update() override;

	protected:

		virtual void onCollisionEnter(Collider* collider, Collider* other, Vector3 collisionPoint) override;

		virtual void onCollisionExit(Collider* collider, Collider* other) override;

	};

	class SphericalRigidBody : public RigidBody {

		virtual void onCollisionEnter(Collider* collider, Collider* other, Vector3 collisionPoint) override;

	};

}