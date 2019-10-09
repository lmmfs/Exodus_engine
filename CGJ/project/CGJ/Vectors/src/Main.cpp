#include "Vector.h"

using namespace std;
using namespace exodus_engine;
using namespace maths;

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

	for (int i = 0; i < 3; i++) {
		cout << v1 << " sobre " << list[i] << v1.rodrigues(list[i], pi / 2) << std::endl;
		cout << v2 << " sobre " << list[i] << v2.rodrigues(list[i], pi / 2) << std::endl;
		cout << v3 << " sobre " << list[i] << v3.rodrigues(list[i], pi / 2) << std::endl;
	}
	
}
