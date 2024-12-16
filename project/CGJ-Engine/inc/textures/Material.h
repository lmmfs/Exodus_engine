#pragma once
#include "maths/Vector.h"

namespace engine {
	struct Material {
		float ambientStrength;
		float specularStrength;
		float shininess;
		float transparency;
		int materialType;

		Material();
		Material(float newAmbient, float newSpecular, float newShininess, float newTransperance, int materialType);

		void setAmbientStrength(float newAmbient) { ambientStrength = newAmbient; }
		void setSpecularStrength(float newSpecular) { specularStrength = newSpecular; }
		void setShininess(float newShininess) { shininess = newShininess; }
		void setTransparency(float newTransperance) { transparency = newTransperance; }
		void setMaterialType(int type) { materialType = type; }

		float getAmbientStrength() { return ambientStrength; }
		float getSpecularStrength() { return specularStrength; }
		float getShininess() { return shininess; }
		float getTransparency() { return transparency; }
		int getMaterialType() { return materialType; }
		bool isTranslucent();

		static Material* parseMaterial();
		static Material* parseMaterial(float newAmbient, float newSpecular, float newShininess, float newTransperance, int materialType);

	};
}