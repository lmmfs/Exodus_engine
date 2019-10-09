#include<iostream>
#include <cmath>


namespace exodus_engine {
	namespace maths {

		struct mat2;
		struct mat3;
		struct mat4;
		struct vec2;
		struct vec3;
		struct vec4;


		struct mat2
		{
			float elements[4];

			mat2();
			mat2(const float& diagonal);
			mat2(const float& a, const float& b, const float& c, const float& d);

			//void setValue(const float& row, const float& colunn, const float& value);

			mat2& add(const mat2& matrix);
			mat2& subtrack(const mat2& matrix);
			mat2& Multiply(const mat2& matrix);
			mat2& Multiply(const vec2& vector);
			mat2& Multiply(float scalar);


			friend mat2& operator+(mat2& left, const mat2& right);
			friend mat2& operator-(mat2& left, const mat2& right);
			friend mat2& operator*(mat2 left, float scalar);
			friend mat2& operator*(float scalar, mat2 left);
			friend mat2& operator*(mat2& left, const mat2& right);
			friend mat2& operator*(vec2& left, const mat2& right);
			friend mat2& operator*(mat2& left, const vec2& right);

			mat2& Transponse();
			float Determinant();
			mat2& Inverse();



		};
	}
}

