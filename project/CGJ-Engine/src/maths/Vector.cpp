#include "maths/Vector.h"
#include "Utils.h"

namespace engine {


		static const float DELTA = 0.0001f;

		/****Vector2D****/
		Vector2::Vector2() :x(0), y(0) {}
		Vector2::Vector2(const float& scalar) : x(scalar), y(scalar) {}
		Vector2::Vector2(const float& x, const float& y) : x(x), y(y) {}
		Vector2::Vector2(const Vector2& vector) : x(vector.x), y(vector.y) {}
		Vector2::Vector2(const Vector3& vector) : x(vector.x), y(vector.y) {}

		Vector2 Vector2::Add(const Vector2 vector) {
			x += vector.x;
			y += vector.y;
			return Vector2(x, y);
		}
		Vector2 Vector2::Subtract(const Vector2 vector) {
			x -= vector.x;
			y -= vector.y;
			return Vector2(x, y);
		}
		Vector2 Vector2::Multiply(float scalar) {
			x *= scalar;
			y *= scalar;
			return Vector2(x, y);
		}

		void Vector2::clean() {
			x = Math::cleanFloat(x, DELTA);
			y = Math::cleanFloat(y, DELTA);
		}

		float Vector2::operator[] (int i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			default: throw "Unsupported index";
			}
		}

		Vector2 operator+(Vector2 left, const Vector2 right) {
			return left.Add(right);
		}
		Vector2 operator-(Vector2 left, const Vector2 right) {
			return left.Subtract(right);
		}
		Vector2 operator*(Vector2 vector, float value) {
			return vector.Multiply(value);
		}
		Vector2 operator*(float value, Vector2 vector) {
			return vector.Multiply(value);
		}
		Vector2 Vector2::operator+=(const Vector2 vector) {
			return Add(vector);
		}
		Vector2 Vector2::operator-=(const Vector2 vector) {
			return Subtract(vector);
		}
		Vector2 Vector2::operator*=(const float scalar) {
			return Multiply(scalar);
		}
		Vector2 operator-(const Vector2 vector) {
			return Vector2(-vector.x, -vector.y);
		}
		bool Vector2::operator==(const Vector2 vector) const {
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			return a < DELTA && b < DELTA;
		}
		bool Vector2::operator!=(const Vector2 vector) const {
			return !(*this == vector);
		}
		float Vector2::length() const {
			return sqrt(pow(x, 2) + pow(y, 2));
		}
		float Vector2::dot(const Vector2 vector) const {
			return x * vector.x + y * vector.y;
		}
		Vector2 Vector2::normalize() const {
			float len = length();
			return Vector2(x / len, y / len);
		}
		std::ostream& operator<<(std::ostream& stream, const Vector2 vector) {
			stream << "vec2 (" << vector.x << "," << vector.y << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, Vector2 vector) {
			float tX, tY;
			is >> tX >> tY;
			vector = Vector2(tX, tY);
			return is;
		}

		/******Vector3D*****/

		Vector3::Vector3() : x(0), y(0), z(0) {}
		Vector3::Vector3(const float& scalar) : x(scalar), y(scalar), z(scalar) {}
		Vector3::Vector3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}
		Vector3::Vector3(const Vector2& vector) : x(vector.x), y(vector.y), z(0) {}
		Vector3::Vector3(const float& x, const float& y) : x(x), y(y), z(0) {}
		Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
		Vector3::Vector3(const Vector4& other) : x(other.x), y(other.y), z(other.z) {}

		Vector3 Vector3::Add(const Vector3 vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}
		Vector3 Vector3::Subtract(const Vector3 vector) {
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}
		Vector3 Vector3::Multiply(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		void Vector3::clean() {
			x = Math::cleanFloat(x, DELTA);
			y = Math::cleanFloat(y, DELTA);
			z = Math::cleanFloat(z, DELTA);
		}

		float Vector3::operator[] (int i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: throw "Unsupported index";
			}
		}

		Vector3 operator+(Vector3 left, const Vector3 right) {
			Vector3 a = left.Add(right);
			return a;
		}
		Vector3 operator-(Vector3 left, const Vector3 right) {
			Vector3 a = left;
			return a.Subtract(right);
		}
		Vector3 operator*(Vector3 vector, float value) {
			Vector3 a = vector;
			return a.Multiply(value);
		}
		Vector3 operator*(float value, Vector3 vector) {
			Vector3 a = vector;
			return a.Multiply(value);
		}
		Vector3 Vector3::operator+=(const Vector3 vector) {
			return Add(vector);
		}
		Vector3 Vector3::operator-=(const Vector3 vector) {
			return Subtract(vector);
		}
		Vector3 Vector3::operator*=(const float scalar) {
			return Multiply(scalar);
		}
		Vector3 operator-(const Vector3 vector) {
			return Vector3(-vector.x, -vector.y, -vector.z);
		}
		bool Vector3::operator==(const Vector3 vector) const {
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			float c = fabs(z - vector.z);
			return a < DELTA && b < DELTA && c < DELTA;
		}
		bool Vector3::operator!=(const Vector3 vector) const {
			return !(*this == vector);
		}
		Vector3 Vector3::cross(const Vector3 vector) const {
			return Vector3((y * vector.z) - (z * vector.y), (z * vector.x) - (x * vector.z), (x * vector.y) - (y * vector.x));
		}
		float Vector3::dot(const Vector3 vector) const {
			return x * vector.x + y * vector.y + z * vector.z;
		}
		Vector3 Vector3::normalize() const {
			float len = length();
			return Vector3(x / len, y / len, z / len);
		}
		float Vector3::length() const {
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		Vector3 Vector3::rodrigues(Vector3 axis, float angle) const {

			float cos_ang = cos(angle);
			float sin_ang = sin(angle);
			Vector3 rot = (cos_ang * (*this)) + (sin_ang * axis.cross((*this))) + (axis * axis.dot((*this)) * (1 - cos_ang));
			return rot;
		}
		Vector3 Vector3::lerp(Vector3 vector, float t)
		{
			Vector3 inter = (1 - t) * (*this) + t * vector;
			return inter;
		}
		Vector3 Vector3::sLerp(Vector3 vector, float t)
		{
			float cos_angle = dot(vector);
			float angle = (float)acos(cos_angle);
			Vector3 inter = (sin((1 - t) * angle) / sin(angle)) * (*this) + (sin(t * angle) / sin(angle)) * vector;
			return Vector3();
		}
		std::ostream& operator<<(std::ostream& stream, const Vector3 vector) {
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, Vector3 vector) {
			float tX, tY, tZ;
			is >> tX >> tY >> tZ;
			vector = Vector3(tX, tY);
			return is;
		}


		/******Vector4D******/

		Vector4::Vector4() {
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}
		Vector4::Vector4(float scalar) {
			this->x = scalar;
			this->y = scalar;
			this->z = scalar;
			this->w = 1;
		}
		Vector4::Vector4(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 1;
		}
		Vector4::Vector4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Vector4::Vector4(const Vector3& vector) {
			this->x = vector.x;
			this->y = vector.y;
			this->z = vector.z;
			this->w = 1;
		}
		Vector4::Vector4(const Vector2& vector) {
			this->x = vector.x;
			this->y = vector.y;
			this->z = 0;
			this->w = 1;
		}
		Vector4 Vector4::Add(const Vector4 other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return Vector4(x, y, z);
		}
		Vector4 Vector4::Subtract(const Vector4 other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return Vector4(x, y, z);
		}
		Vector4 Vector4::Multiply(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return Vector4(x, y, z);
		}

		void Vector4::clean() {
			x = Math::cleanFloat(x, DELTA);
			y = Math::cleanFloat(y, DELTA);
			z = Math::cleanFloat(z, DELTA);
			w = Math::cleanFloat(w, DELTA);
		}

		float Vector4::operator[] (int i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			case 3: return w;
			default: throw "Unsupported index";
			}
		}

		Vector4 operator+(Vector4 left, const Vector4 right) {
			return left.Add(right);
		}
		Vector4 operator-(Vector4 left, const Vector4 right) {
			return left.Subtract(right);
		}
		Vector4 operator*(Vector4 vector, float value) {
			return vector.Multiply(value);
		}
		Vector4 operator*(float value, Vector4 vector) {
			return vector.Multiply(value);
		}
		Vector4 Vector4::operator+=(const Vector4 vector) {
			return Add(vector);
		}
		Vector4 Vector4::operator-=(const Vector4 vector) {
			return Subtract(vector);
		}
		Vector4 Vector4::operator*=(const float scalar) {
			return Multiply(scalar);
		}
		Vector4 operator-(const Vector4 vector) {
			return Vector4(-vector.x, -vector.y, -vector.z, -vector.w);
		}
		bool Vector4::operator==(const Vector4 vector) const {
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			float c = fabs(z - vector.z);
			float d = fabs(w - vector.w);
			return a < DELTA && b < DELTA && c < DELTA && d < DELTA;
		}
		bool Vector4::operator!=(const Vector4 vector) const {
			return !(*this == vector);
		}
		
		Vector4 Vector4::normalize() const {
			float len = length();
			return Vector4(x / len, y / len, z / len, w / len);
		}

		float Vector4::length() const {
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
		}

		float Vector4::dot(const Vector4 other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}
		std::ostream& operator<<(std::ostream& stream, const Vector4 vector) {
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, Vector4 vector) {
			float tX, tY, tZ;
			is >> tX >> tY >> tZ;
			vector = Vector4(tX, tY, tZ);
			return is;
		}
	
}
