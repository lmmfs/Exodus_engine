#pragma once

#include "Updatable.h"
#include "scene/SceneNodeComponent.h"
#include "mesh/Mesh.h"

namespace engine {

	class CollisionListener;

	class Collider : public Updatable, public Mesh, public SceneNodeComponent {

	private:

		std::vector<CollisionListener*> listeners;

		std::vector<Collider*> inCollision;

	public:

		virtual bool isInside(Vertex, std::vector<float>) const = 0;
		
		std::vector<CollisionListener*> getListeners() const;

		void addListener(CollisionListener*);

		virtual const std::vector<Vertex> getVertices() const override;

		const float getHeight() const;

		const float getWidth() const;

	public:

		virtual void update() override;

	};

	class BoxCollider : public Collider {

	public:

		BoxCollider(Mesh* mesh);

		virtual bool isInside(Vertex, std::vector<float>) const override;

	};

	class MeshCollider : public Collider {

	public:

		MeshCollider(Mesh* mesh);

		virtual bool isInside(Vertex, std::vector<float>) const override;

	};

}