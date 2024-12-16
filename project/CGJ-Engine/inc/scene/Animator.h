#pragma once
#include "maths/Matrix.h"
#include "scene/SceneNode.h"

namespace engine {

	class Animator {

	private:

		Matrix4 jump;

		float progress = 1.01f;

		Vector3 translation;

		Vector3 origTranslation;

		Quaternion rotation;

		Quaternion origRotation;

		Vector3 scaling;

		Vector3 origScaling;

		SceneNode* node;

		bool translate = false, rotate = false, scale = false;

		const float rate = 0.01f;

		Quaternion interpolateAngle(float k);
		Vector3 interpolateDistance(float k);
		Vector3 interpolateSize(float k);

	public:
		Animator(SceneNode*);

		void setTranslation(Vector3);

		void setRotation(Quaternion);

		void setScale(Vector3);

		void animate();
	};

}