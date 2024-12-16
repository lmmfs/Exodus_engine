#include "scene/SceneGraph.h"

namespace engine {

	SceneGraph::SceneGraph() {
		this->root = nullptr;
		this->camera = nullptr;
	}

	void SceneGraph::setCamera(Camera* camera) {
		this->camera = camera;
	}

	void SceneGraph::setLightCamera(Camera* lightCam) {
		this->lightCamera = lightCam;
	}

	SceneNode* SceneGraph::getRoot() {
		if (root != nullptr) {
			return root;
		}

		this->root = new SceneNode();
		this->root->setWorldMatrix(nullptr);

		return root;
	}

	SceneNode* SceneGraph::createNode() {

		return getRoot()->createNode();

	}

	void SceneGraph::draw() {

		camera->draw();

		root->draw();
	}

	void SceneGraph::drawDepthMap(engine::ShaderProgram* shader) {
		root->drawShadow(shader);
	}

}