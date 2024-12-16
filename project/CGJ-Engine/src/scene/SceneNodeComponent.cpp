#include "scene/SceneNodeComponent.h"

namespace engine {

	SceneNodeComponent::SceneNodeComponent() {
		this->node = nullptr;
	}

	SceneNode* SceneNodeComponent::getSceneNode() const {
		return this->node;
	}

	void SceneNodeComponent::setSceneNode(SceneNode* node) {
		this->node = node;
	}

}