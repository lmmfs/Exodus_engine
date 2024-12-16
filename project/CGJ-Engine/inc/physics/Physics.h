#pragma once

#define EARTH_GRAVITY 9.81f

#include "maths/Vector.h"
#include "physics/RigidBody.h"
#include "physics/Collider.h"
#include <vector>

namespace engine {

	/**
	* Main Physics Engine class
	*/
	class Physics : public Updatable {

		////////////////////
		// Static members //
		////////////////////

	private: 
		
		static Physics* instance;

	public:

		static Physics* getInstance();

		static RigidBody* newRigidBody(const float = 1.0f, const float = 1.0f);

		static RigidBody* newSphericalRigidBody(const float = 1.0f, const float = 1.0f);

		static Collider* newBoxCollider(Mesh*);

		static Collider* newMeshCollider(Mesh*);

		static std::vector<Collider*> getColliders(std::vector<Collider*> = {});

		/////////////
		// Members //
		/////////////

	private:

		// The Gravity value
		float gravity;

		Vector3 gravityVector;

		std::vector<Updatable*> components;

		bool drawColliders = false;

		//////////////////////////////////////////////
		// Constructor								//
		// Should only be used by the static method //
		//////////////////////////////////////////////
	
	private:

		Physics();


	public:

		////////////////
		// Properties //
		////////////////

		/**
		* Gets the gravity force value
		*
		* @return the gravity
		*/
		const float getGravity();

		/**
		* Sets the gravity force value
		*
		* @param gravity The force value
		*/
		void setGravity(const float);

		/**
		* Gets the gravity force value
		*
		* @return the gravity
		*/
		const Vector3 getGravityVector();

		/**
		* Creates a new RigidBody component
		*
		* @param mass The mass of the RigidBody
		* @param bounciness The bounciness of the RigidBody
		* @return the rigidbody
		*/
		RigidBody* createRigidBody(const float = 1.0f, const float = 1.0f);

		/**
		* Creates a new SphericalRigidBody component
		*
		* @param mass The mass of the RigidBody
		* @param bounciness The bounciness of the RigidBody
		* @return the rigidbody
		*/
		SphericalRigidBody* createSphericalRigidBody(const float = 1.0f, const float = 1.0f);

		/**
		* Creates a new RigidBody component
		*
		* @param mass The mass of the RigidBody
		* @return the rigidbody
		*/
		BoxCollider* createBoxCollider(Mesh*);

		/**
		* Creates a new RigidBody component
		*
		* @param mass The mass of the RigidBody
		* @return the rigidbody
		*/
		MeshCollider* createMeshCollider(Mesh*);

		/**
		* Toggle if colliders should be drawn or not (debug purposes)
		*/
		void toggleShowColliders();

		/**
		* Flag that indicates if colliders should be drawn (debug purposes)
		*
		* @return true if colliders should appear, false otherwise
		*/
		bool showColliders() const;

	public:

		void update() override;

	};

}