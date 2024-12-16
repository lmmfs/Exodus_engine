#pragma once
#include "Drawable.h"
#include "camera/Camera.h"
#include "scene/SceneNode.h"

namespace engine {

	class SceneGraph : public Drawable {

	private:

		Camera* camera = NULL;
		Camera* lightCamera = NULL;

		SceneNode* root = NULL;

	public:

		SceneGraph();

		void setCamera(Camera*);
		void setLightCamera(Camera*);

		SceneNode* getRoot();

		SceneNode* createNode();

		////////////////////////////////////////////////
		// Drawable - @see Drawable.h for definitions //
		////////////////////////////////////////////////

	public:

		void draw() override;
		void drawDepthMap(engine::ShaderProgram* shader);

	};

}