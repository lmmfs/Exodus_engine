#include "Vector.h"

namespace exodus_engine {
	namespace maths {

		static const float DELTA = 0.0001f;
		
		/****Vector2D****/
		vec2::vec2() :x(0), y(0) {}
		vec2::vec2(const float& scalar) : x(scalar), y(scalar) {}
		vec2::vec2(const float& x, const float& y) : x(x), y(y) {}
		vec2::vec2(const vec2& vector) : x(vector.x), y(vector.y) {}
		vec2::vec2(const vec3& vector) : x(vector.x), y(vector.y) {}

		vec2& vec2::add(const vec2& vector) {
			x += vector.x;
			y += vector.y;
			return *this;
		}
		vec2& vec2::subtrack(const vec2& vector) {
			x -= vector.x;
			y -= vector.y;
			return *this;
		}
		vec2& operator+(vec2& left, const vec2& right) {
			return left.add(right);
		}
		vec2& operator-(vec2& left, const vec2& right) {
			return left.subtrack(right);
		}
		vec2 operator*(vec2 vector, float value){
			return vec2(vector.x * value, vector.y * value);
		}
		vec2 operator*(float value , vec2 vector){
			return vec2(vector.x * value, vector.y * value);
		}
		vec2& vec2::operator+=(const vec2& vector) {
			return *this + vector;
		}
		vec2& vec2::operator-=(const vec2& vector) {
			return *this - vector;
		}
		vec2 operator-(const vec2& vector) {
			return vec2(-vector.x, -vector.y);
		}
		bool vec2::operator==(const vec2& vector) const {
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			return a < DELTA && b < DELTA;
		}
		bool vec2::operator!=(const vec2& vector) const {
			return !(*this == vector);
		}
		float vec2::Lenght(const vec2& vector) const{
			float a = x - vector.x;
			float b = y - vector.y;
			return sqrt(a * a + b * b);
		}
		float vec2::Dot(const vec2& vector) const{
			return x * vector.x + y * vector.y;
		}
		float vec2::Magnitude() const{
			return sqrt(x * x + y * y);
		}
		vec2 vec2::Normalise() const{
			float length = Magnitude();
			return vec2(x / length, y / length);
		}
		std::ostream& operator<<(std::ostream& stream, const vec2& vector) {
			stream << "vec2 (" << vector.x << "," << vector.y << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, vec2& vector) {
			float tX, tY;
			is >> tX >> tY;
			vector = vec2(tX, tY);
			return is;
		}

		/******Vector3D*****/
		vec3::vec3() : x(0), y(0), z(0){}
		vec3::vec3(const float& scalar) : x(scalar), y(scalar), z(scalar) {}
		vec3::vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}
		vec3::vec3(const vec2& vector) : x(vector.x), y(vector.y), z(0) {}
		vec3::vec3(const float& x, const float& y) : x(x), y(y), z(0) {}
		vec3::vec3(const vec3& other) : x(other.x), y(other.y), z(other.z) {}
		vec3::vec3(const vec4& other) : x(other.x), y(other.y), z(other.z) {}
		
		vec3& vec3::add(const vec3& vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}
		vec3& vec3::subtrack(const vec3& vector) {
			x -= vector.x;
			y -= vector.y;
			z += vector.z;
			return *this;
			return *this;
		}
		vec3& operator+(vec3& left, const vec3& right) {
			return left.add(right);
		}
		vec3& operator-(vec3& left, const vec3& right) {
			return left.subtrack(right);
		}
		vec3 operator*(vec3 vector, float value){
			return vec3(vector.x * value, vector.y * value, vector.z * value);
		}
		vec3 operator*(float value, vec3 vector){
			return vec3(vector.x * value, vector.y * value, vector.z * value);
		}
		vec3& vec3::operator+=(const vec3& vector) {
			return *this + vector;
		}
		vec3& vec3::operator-=(const vec3& vector) {
			return *this - vector;
		}
		vec3 operator-(const vec3& vector){
			return vec3(-vector.x, -vector.y, -vector.z);
		}
		bool vec3::operator==(const vec3& vector) const {
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			float c = fabs(z - vector.z);
			return a < DELTA && b < DELTA && c < DELTA;
		}
		bool vec3::operator!=(const vec3& vector) const {
			return !(*this == vector);
		}
		vec3 vec3::Cross(const vec3& vector){
			return vec3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
		}
		float vec3::Dot(const vec3& vector){
			return x * vector.x + y * vector.y + z * vector.z;
		}
		float vec3::Magnitude() const{
			return sqrt(x * x + y * y + z * z);
		}
		vec3 vec3::Normalize() const{
			float length = Magnitude();
			return vec3(x / length, y / length, z / length);
		}
		float vec3::Lenght(const vec3& vector) const{
			float a = x - vector.x;
			float b = y - vector.y;
			float c = z - vector.z;
			return sqrt(a * a + b * b + c * c);
		}
		std::ostream& operator<<(std::ostream& stream, const vec3& vector){
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, vec3& vector) {
			float tX, tY, tZ;
			is >> tX >> tY >> tZ;
			vector = vec3(tX, tY);
			return is;
		}

		/******Vector4D******/

		vec4::vec4() {
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		vec4::vec4(float scalar) {
			this->x = scalar;
			this->y = scalar;
			this->z = scalar;
			this->w = 1;
		}
		vec4::vec4(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 1;
		}
		vec4::vec4(const vec3& vector) {
			this->x = vector.x;
			this->y = vector.y;
			this->z = vector.z;
			this->w = 1;
		}
		vec4::vec4(const vec2& vector) {
			this->x = vector.x;
			this->y = vector.y;
			this->z = 0;
			this->w = 1;
		}
		vec4& vec4::Add(const vec4& other){
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		vec4& vec4::Subtract(const vec4& other){
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		vec4 operator+(vec4 left, const vec4& right){
			return left.Add(right);
		}
		vec4 operator-(vec4 left, const vec4& right){
			return left.Subtract(right);
		}
		vec4 operator*(vec4 vector, float value) {
			return vec4(vector.x * value, vector.y * value, vector.z * value);
		}
		vec4 operator*(float value, vec4 vector) {
			return vec4(vector.x * value, vector.y * value, vector.z * value);
		}
		vec4& vec4::operator+=(const vec4& vector){
			return Add(vector);
		}
		vec4& vec4::operator-=(const vec4& vector) {
			return Subtract(vector);
		}
		bool vec4::operator==(const vec4& vector){
			float a = fabs(x - vector.x);
			float b = fabs(y - vector.y);
			float c = fabs(z - vector.z);
			float d = fabs(w - vector.w);
			return a < DELTA && b < DELTA && c < DELTA && d < DELTA;
		}
		bool vec4::operator!=(const vec4& vector){
			return !(*this == vector);
		}
		float vec4::Dot(const vec4& other){
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}
		std::ostream& operator<<(std::ostream& stream, const vec4& vector) {
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
		std::istream& operator>>(std::istream& is, vec4& vector) {
			double tX, tY, tZ;
			is >> tX >> tY >> tZ;
			vector = vec4(tX, tY, tZ);
			return is;
		}
	}
}
