#include "textures/Material.h"
namespace engine {

	Material::Material() {
		this->ambientStrength = 1.0;
		this->specularStrength = 1.0;
		this->shininess = 1.0f;
		this->transparency = 1.0f;
		this->materialType = 0;
	}

	Material::Material(float newAmbient, float newSpecular, float newShininess, float newTransparency, int type) {
		this->ambientStrength = newAmbient;
		this->specularStrength = newSpecular;
		this->shininess = newShininess;
		this->transparency = newTransparency;
		this->materialType = type;
	}

	bool Material::isTranslucent() {
		if (transparency < 1.0f) return true;
		else return false;
	}

	Material* Material::parseMaterial() {
		Material* m = new Material();
		return m;
	}

	Material* Material::parseMaterial(float newAmbient, float newSpecular, float newShininess, float newTransparency, int materialType) {
		Material* m = new Material(newAmbient, newSpecular, newShininess, newTransparency, materialType);
		return m;
	}
}