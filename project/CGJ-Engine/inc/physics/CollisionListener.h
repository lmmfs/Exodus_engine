#pragma once
#include "physics/Collider.h"

namespace engine {

	class CollisionListener {

	public:

		virtual void onCollisionEnter(Collider* collider, Collider* other, Vector3 collisionPoint) = 0;

		virtual void onCollisionExit(Collider* collider, Collider* other) = 0;

	};

}