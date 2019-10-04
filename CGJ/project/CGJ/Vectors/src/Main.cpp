#include "Vector.h"

using namespace std;
using namespace exodus_engine;
using namespace maths;

vec3 rod(vec3 vector, vec3 axis, float angle) {
	float cos_ang = cos(angle);
	float sin_ang = sin(angle);
	vec3 rot = (cos_ang * vector) .add( (sin_ang * axis.Cross(vector))).add(((axis * axis.Dot(vector)) * (1 - cos_ang)));
	return rot;
}

int main()
{
	float pi = 3.14159265359;

	vec3  v1 = vec3(2, 0, 0);
	vec3  v2 = vec3(0, 3, 0);
	vec3  v3 = vec3(0, 0, 4);

	vec3 a1 = v1.Normalize();
	vec3 a2 = v2.Normalize();
	vec3 a3 = v3.Normalize();

	vec3 list[3];
	list[0] = a1;
	list[1] = a2;
	list[2] = a3;

	for (int i = 0; i<3 ; i++){
		cout << rod(v1, list[i], pi / 2) << std::endl;
		cout << rod(v2, list[i], pi / 2) << std::endl;
		cout << rod(v3, list[i], pi / 2) << std::endl;
	}
	
}
