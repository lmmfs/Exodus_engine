#pragma once

namespace engine {

	class SceneNode;

	class SceneNodeComponent {

	protected:

		SceneNode* node;

	public:

		SceneNodeComponent();

		SceneNode* getSceneNode() const;

		virtual void setSceneNode(SceneNode*);

	};

}