#include<iostream>
#include <cmath>

namespace exodus_engine {
	namespace maths {
		
		struct vec2;
		struct vec3;
		struct vec4;

		struct vec2
		{
			float x, y;

			vec2();
			vec2(const float& scalar);
			vec2(const float& x, const float& y);
			vec2(const vec2& vector);
			vec2(const vec3& vector);

			vec2& add(const vec2& vector);
			vec2& subtrack(const vec2& vector);

			friend vec2& operator+(vec2& left, const vec2& right);
			friend vec2& operator-(vec2& left, const vec2& right);
			friend vec2 operator*(vec2 left, float value);
			friend vec2 operator*(float value, vec2 left);

			vec2& operator+=(const vec2& vector);
			vec2& operator-=(const vec2& vector);

			friend vec2 operator-(const vec2& vector);

			bool operator==(const vec2& vector) const;
			bool operator!=(const vec2& vector) const;

			float Magnitude() const;
			vec2 Normalise() const;
			float Lenght(const vec2& vector) const;
			float Dot(const vec2& vector) const;

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
			friend std::istream& operator>>(std::istream& os, vec2& vector);
		};

		
		struct vec3 {
			float x, y, z;

			vec3();
			vec3(const float& scalar);
			vec3(const float& x, const float& y, const float& z);
			vec3(const vec2& vector);
			vec3(const float& x, const float& y);
			vec3(const vec3& vector);
			vec3(const vec4& vector);

			vec3& add(const vec3& vector);
			vec3& subtrack(const vec3& vector);

			friend vec3& operator+(vec3& left, const vec3& right);
			friend vec3& operator-(vec3& left, const vec3& right);
			friend vec3 operator*(vec3 left, float value);
			friend vec3 operator*(float value, vec3 left);

			vec3& operator+=(const vec3& vector);
			vec3& operator-=(const vec3& vector);

			friend vec3 operator-(const vec3& vector);

			bool operator==(const vec3& vector) const;
			bool operator!=(const vec3& vector) const;

			vec3 Cross(const vec3& vector);
			float Dot(const vec3& vector);
			float Magnitude() const;
			vec3 Normalize() const;
			float Lenght(const vec3& vector) const;
			vec3 rod(vec3 vector, float angle);

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
			friend std::istream& operator>>(std::istream& os, vec3& vector);
		};

		struct vec4{
			float x, y, z, w;

			vec4();
			vec4(float scalar);
			vec4(float x, float y, float z);
			vec4(const vec2& vector);
			vec4(const vec3& vector);

			vec4& Add(const vec4& vector);
			vec4& Subtract(const vec4& vector);

			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 vector, float value);
			friend vec4 operator*(float value, vec4 vector);

			vec4& operator+=(const vec4& vector);
			vec4& operator-=(const vec4& vector);

			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			float Dot(const vec4& vector);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
			friend std::istream& operator>>(std::istream& os, vec4& vector);
		};
	}
}
