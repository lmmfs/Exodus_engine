#include "scene/Animator.h"
#include "maths/Quaternion.h"

namespace engine {

	Animator::Animator(SceneNode* node) {
		this->node = node;
		this->translation = *node->getPosition();
		this->rotation = *node->getRotation();
		this->scaling = *node->getScale();
	}

	void Animator::setTranslation(Vector3 translation) {
		this->translation = translation;
		this->origTranslation = *node->getPosition();
		translate = true;
		if (progress == 0.0f || !(progress < 1.0f)) {
			this->progress = 0.0f;
		}
		else {
			this->progress = 1.0f - progress;
		}
	}

	void Animator::setRotation(Quaternion rotation) {
		this->rotation = rotation;
		this->origRotation = *node->getRotation();
		rotate = true;
		if (progress == 0.0f || !(progress < 1.0f)) {
			this->progress = 0.0f;
		}
		else {
			this->progress = 1.0f - progress;
		}
	}

	void Animator::setScale(Vector3 scale) {
		this->scaling = scale;
		this->origScaling = *node->getScale();
		scale = true;
		if (progress == 0.0f || !(progress < 1.0f)) {
			this->progress = 0.0f;
		} else {
			this->progress = 1.0f - progress;
		}
	}

	Quaternion Animator::interpolateAngle(float k)
	{
		Quaternion qrot = this->origRotation.lerp(this->rotation, k);
		return qrot;
	}

	Vector3 Animator::interpolateDistance(float k)
	{
		return this->origTranslation.lerp(this->translation, k);
	}

	Vector3 Animator::interpolateSize(float k) {
		return this->origScaling.lerp(this->scaling, k);
	}

	void Animator::animate() {
		if (translate || rotate || scale) {
			if (!translate) {
				this->origTranslation = this->translation;
				this->translation = Vector3();
			}
			if (!rotate) {
				this->origRotation = this->rotation;
				this->rotation = Quaternion();
			}
			if (!scale) {
				this->origScaling = this->scaling;
				this->scaling = Vector3();
			}
			translate = rotate = scale = false;
		}
		if (progress < 1.0f) {

			// Interpolate translation
			node->setPosition(interpolateDistance(progress));

			// Interpolate rotation
			node->setRotation(interpolateAngle(progress));

			// Interpolate scale
			//node->setScale(interpolateSize(progress));

			progress += rate;

		}
	}

}