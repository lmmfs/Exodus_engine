#include "maths/Matrix.h"
#include "Utils.h"



namespace engine {
		//elements[row + col * with]
		static const float DELTA = 0.0001f;

		/*************** Matrix 2*2 ******************/
		Matrix2::Matrix2()
		{
			memset(elements, 0, SIZE * SIZE * sizeof(float));
		}
		Matrix2::Matrix2(const float& diagonal)
		{
			memset(elements, 0, SIZE * SIZE * sizeof(float));

			elements[0 + 0 * SIZE] = diagonal;
			elements[1 + 1 * SIZE] = diagonal;
		}
		Matrix2::Matrix2(const Vector2& col0, const Vector2& col1)
		{
			cols[0] = col0;
			cols[1] = col1;
		}
		Matrix2::Matrix2(float* elements)
		{
			memcpy(this->elements, elements, SIZE * SIZE * sizeof(float));
		}

		Matrix2::Matrix2(const Matrix2& matrix)
		{
			memcpy(this->elements, matrix.elements, SIZE * SIZE * sizeof(float));
		}

		Matrix2 Matrix2::Add(const Matrix2 matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] += matrix.elements[i];
			}
			return Matrix2(elements);
		}
		Matrix2 Matrix2::Subtract(const Matrix2 matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] -= matrix.elements[i];
			}
			return Matrix2(elements);
		}
		Matrix2 Matrix2::Multiply(const Matrix2 matrix)
		{
			float result[4];
			memset(result, 0, 2 * 2 * sizeof(float));
			for (int row = 0; row < SIZE; row++) {

				for (int col = 0; col < SIZE; col++) {

					float sum = 0.0f;

					for (int e = 0; e < SIZE; e++) {
						sum += elements[col + e * SIZE] * matrix.elements[e + row * SIZE];
					}

					result[col + row * SIZE] = sum;
				}
			}
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] = result[i];
			}
			return Matrix2(elements);
		}
		Matrix2 Matrix2::Multiply(float scalar)
		{
			for (int i = 0; i < 4; i++) {
				elements[i] *= scalar;
			}
			return Matrix2(elements);
		}

		Vector2 Matrix2::operator[] (int i) const {
			return Vector2(elements[i], elements[i + 1]);
		}

		Matrix2 operator+(Matrix2 left, const Matrix2 right)
		{
			return left.Add(right);
		}
		Matrix2 operator-(Matrix2 left, const Matrix2 right)
		{
			return left.Subtract(right);
		}
		Matrix2 operator*(Matrix2 left, float scalar)
		{
			return left.Multiply(scalar);
		}
		Matrix2 operator*(float scalar, Matrix2 left)
		{
			return left.Multiply(scalar);
		}
		Matrix2 operator*(Matrix2 left, const Matrix2 right)
		{
			return left.Multiply(right);
		}
		Vector2 operator*(Vector2 vector, Matrix2 matrix)
		{
			float mx, my;
			mx = vector.x * matrix.elements[0 + 0 * 2] + vector.y * matrix.elements[1 + 0 * 2];
			my = vector.x * matrix.elements[0 + 1 * 2] + vector.y * matrix.elements[1 + 1 * 2];
			return Vector2(mx, my);
		}
		Vector2 operator*(Matrix2 matrix, Vector2 vector)
		{
			float x = matrix.elements[0] * vector.x + matrix.elements[2] * vector.y;
			float y = matrix.elements[1] * vector.x + matrix.elements[3] * vector.y;
			return Vector2(x, y);
		}
		bool Matrix2::operator==(const Matrix2& matrix)
		{
			bool eq = true;
			for (int r = 0; r < SIZE; r++) {
				for (int c = 0; c < SIZE; c++) {
					if (fabs(elements[r + c * SIZE] - matrix.elements[r + c * SIZE]) > DELTA) {
						eq = false;
						break;
					}
				}
			}
			return eq;
		}
		bool Matrix2::operator!=(const Matrix2& matrix)
		{
			return !(*this == matrix);
		}
		void Matrix2::clean()
		{
			for (int i = 0; i < 3 * 3; i++) {
				if (fabs(elements[i]) < DELTA) elements[i] = 0.0f;
			}
		}
		size_t Matrix2::size() {
			return 2 * 2 * sizeof(float);
		}
		Matrix2 Matrix2::transpose()
		{
			float a = elements[1 + 0 * SIZE];
			elements[1 + 0 * SIZE] = elements[0 + 1 * SIZE];
			elements[0 + 1 * SIZE] = a;
			return Matrix2(elements);
		}
		float Matrix2::determinant()
		{
			return elements[0 + 0 * SIZE] * elements[1 + 1 * SIZE] - elements[0 + 1 * SIZE] * elements[1 + 0 * SIZE];
		}
		Matrix2 Matrix2::adjugate()
		{
			elements[2] = -elements[2];
			elements[3] = -elements[3];
			return Matrix2(elements);
		}
		Matrix2 Matrix2::inverse()
		{
			float determinat = (*this).determinant();
			if (determinat != 0) {
				Matrix2 trans = (*this).transpose();
				trans = trans.adjugate();
				return trans * (1 / determinat);
			}
			else {
				std::cout << "Determinat = 0" << std::endl;
				return Matrix2();
			}

		}
		std::ostream& operator<<(std::ostream& stream, const Matrix2& matrix)
		{
			stream << "[" << matrix.elements[0 + 0 * 2] << " " << matrix.elements[0 + 1 * 2] << "]" << std::endl;
			stream << "[" << matrix.elements[1 + 0 * 2] << " " << matrix.elements[1 + 1 * 2] << "]" << std::endl;
			return stream;
		}

		/*************** Matrix 3*3 ******************/

		Matrix3::Matrix3()
		{
			memset(elements, 0, 3 * 3 * sizeof(float));
		}
		Matrix3::Matrix3(const float& diagonal)
		{
			memset(elements, 0, 3 * 3 * sizeof(float));
			elements[0 + 0 * SIZE] = diagonal;
			elements[1 + 1 * SIZE] = diagonal;
			elements[2 + 2 * SIZE] = diagonal;
		}
		Matrix3::Matrix3(float* elements)
		{
			memcpy(this->elements, elements, 3 * 3 * sizeof(float));
		}
		Matrix3::Matrix3(const Matrix4& matrix)
		{
			memset(elements, 0, SIZE * SIZE * sizeof(float));
			for (int r = 0; r < SIZE; r++) {
				for (int c = 0; c < SIZE; c++) {
					elements[r + c * SIZE] = matrix.elements[r + c * SIZE];
				}
			}
		}
		Matrix3::Matrix3(const Matrix3& matrix)
		{
			memcpy(this->elements, matrix.elements, 3 * 3 * sizeof(float));
		}
		Matrix3::Matrix3(const Matrix2& matrix)
		{
			memset(elements, 0, SIZE * SIZE * sizeof(float));
			elements[0 + 0 * SIZE] = matrix.elements[0 + 0 * (SIZE - 1)];
			elements[0 + 1 * SIZE] = matrix.elements[0 + 1 * (SIZE - 1)];
			elements[1 + 0 * SIZE] = matrix.elements[1 + 0 * (SIZE - 1)];
			elements[1 + 1 * SIZE] = matrix.elements[1 + 1 * (SIZE - 1)];
		}
		Matrix3::Matrix3(const Vector3& col0, const Vector3& col1, const Vector3& col2)
		{
			cols[0] = col0;
			cols[1] = col1;
			cols[2] = col2;
		}
		Matrix3 Matrix3::Add(const Matrix3& matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] += matrix.elements[i];
			}
			return *this;
		}
		Matrix3 Matrix3::Subtract(const Matrix3& matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] -= matrix.elements[i];
			}
			return *this;
		}
		Matrix3 Matrix3::Multiply(const Matrix3& matrix)
		{
			float result[9];
			memset(result, 0, 3 * 3 * sizeof(float));

			for (int row = 0; row < SIZE; row++) {

				for (int col = 0; col < SIZE; col++) {

					float sum = 0.0f;

					for (int e = 0; e < SIZE; e++) {
						sum += elements[col + e * SIZE] * matrix.elements[e + row * SIZE];
					}

					result[col + row * SIZE] = sum;
				}

			}

			return Matrix3(result);
		}
		Matrix3 Matrix3::Multiply(float scalar)
		{
			for (int i = 0; i < 9; i++) {
				elements[i] *= scalar;
			}
			return *this;
		}

		Vector3 Matrix3::operator[] (int i) const {
			return Vector3(elements[i], elements[i + 1], elements[i + 2]);
		}

		Matrix3 operator+(Matrix3 left, const Matrix3 right)
		{
			return left.Add(right);
		}
		Matrix3 operator-(Matrix3 left, const Matrix3 right)
		{
			return left.Subtract(right);
		}
		Matrix3 operator*(Matrix3 left, float scalar)
		{
			return left.Multiply(scalar);
		}
		Matrix3 operator*(float scalar, Matrix3 left)
		{
			return left.Multiply(scalar);
		}
		Matrix3 operator*(Matrix3 left, const Matrix3 right)
		{
			return left.Multiply(right);
		}
		Vector3 operator*(Vector3 vector, const Matrix3 matrix)
		{
			float mx, my, mz;
			mx = vector.x * matrix.elements[0 + 0 * 3] + vector.y * matrix.elements[1 + 0 * 3] + vector.z * matrix.elements[2 + 0 * 3];
			my = vector.x * matrix.elements[0 + 1 * 3] + vector.y * matrix.elements[1 + 1 * 3] + vector.z * matrix.elements[2 + 1 * 3];
			mz = vector.x * matrix.elements[0 + 2 * 3] + vector.y * matrix.elements[1 + 2 * 3] + vector.z * matrix.elements[2 + 2 * 3];
			return Vector3(mx, my, mz);
		}
		Vector3 operator*(Matrix3 matrix, Vector3 vector)
		{
			float x = matrix.elements[0] * vector.x + matrix.elements[3] * vector.y + matrix.elements[6] * vector.z;
			float y = matrix.elements[1] * vector.x + matrix.elements[4] * vector.y + matrix.elements[7] * vector.z;
			float z = matrix.elements[2] * vector.x + matrix.elements[5] * vector.y + matrix.elements[8] * vector.z;
			return Vector3(x, y, z);
		}
		bool Matrix3::operator==(const Matrix3& matrix)
		{
			bool eq = true;
			for (int r = 0; r < SIZE; r++) {
				for (int c = 0; c < SIZE; c++) {
					if (fabs(elements[r + c * SIZE] - matrix.elements[r + c * SIZE]) > DELTA) {
						eq = false;
						break;
					}
				}
			}
			return eq;
		}
		bool Matrix3::operator!=(const Matrix3& matrix)
		{
			return !(*this == matrix);
		}
		void Matrix3::clean()
		{
			for (int i = 0; i < 3 * 3; i++) {
				if (fabs(elements[i]) < DELTA) elements[i] = 0.0f;
			}
		}
		size_t Matrix3::size() {
			return 3 * 3 * sizeof(float);
		}
		float Matrix3::determinant()
		{
			float temp[SIZE];
			temp[0] = elements[0] * (elements[4] * elements[8] - elements[5] * elements[7]);
			temp[1] = elements[3] * (elements[1] * elements[8] - elements[2] * elements[7]);
			temp[2] = elements[6] * (elements[1] * elements[5] - elements[2] * elements[4]);
			return temp[0] - temp[1] + temp[2];
		}
		Matrix3 Matrix3::transpose()
		{
			return  Matrix3(
				Vector3((*this).cols[0].x, (*this).cols[1].x, (*this).cols[2].x),
				Vector3((*this).cols[0].y, (*this).cols[1].y, (*this).cols[2].y),
				Vector3((*this).cols[0].z, (*this).cols[1].z, (*this).cols[2].z)
			);
		}
		Matrix3 Matrix3::cofactors()
		{
			float temp[SIZE * SIZE];
			temp[0] = elements[4] * elements[8] - elements[5] * elements[7];
			temp[1] = elements[3] * elements[8] - elements[5] * elements[6];
			temp[2] = elements[3] * elements[7] - elements[4] * elements[6];
			temp[3] = elements[1] * elements[8] - elements[2] * elements[7];
			temp[4] = elements[0] * elements[8] - elements[2] * elements[6];
			temp[5] = elements[0] * elements[7] - elements[1] * elements[6];
			temp[6] = elements[1] * elements[5] - elements[2] * elements[4];
			temp[7] = elements[0] * elements[5] - elements[2] * elements[3];
			temp[8] = elements[0] * elements[4] - elements[1] * elements[3];
			return Matrix3(temp);
		}
		Matrix3 Matrix3::adjugate()
		{
			elements[1] = -elements[1];
			elements[3] = -elements[3];
			elements[5] = -elements[5];
			elements[7] = -elements[7];
			return Matrix3(elements);
		}
		Matrix3 Matrix3::inverse()
		{
			float determinat = (*this).determinant();
			if (determinat != 0) {
				Matrix3 tran = (*this);
				tran = tran.transpose();
				tran = tran.cofactors();
				tran = tran.adjugate();
				tran = tran * (1 / determinat);
				return tran;
			}
			else {
				std::cout << "Determinat = 0" << std::endl;
				return Matrix3();
			}
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix3& matrix)
		{
			stream << "[" << matrix.elements[0 + 0 * 3] << " " << matrix.elements[0 + 1 * 3] << " " << matrix.elements[0 + 2 * 3] << "]" << std::endl;
			stream << "[" << matrix.elements[1 + 0 * 3] << " " << matrix.elements[1 + 1 * 3] << " " << matrix.elements[1 + 2 * 3] << "]" << std::endl;
			stream << "[" << matrix.elements[2 + 0 * 3] << " " << matrix.elements[2 + 1 * 3] << " " << matrix.elements[2 + 2 * 3] << "]" << std::endl;
			return stream;
		}

		/*************** Matrix 4*4 ******************/

		Matrix4::Matrix4()
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
		}
		Matrix4::Matrix4(const float& diagonal)
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
			elements[0 + 0 * SIZE] = diagonal;
			elements[1 + 1 * SIZE] = diagonal;
			elements[2 + 2 * SIZE] = diagonal;
			elements[3 + 3 * SIZE] = diagonal;
		}
		Matrix4::Matrix4(const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3)
		{
			cols[0] = col0;
			cols[1] = col1;
			cols[2] = col2;
			cols[3] = col3;
		}
		Matrix4::Matrix4(float* elements)
		{
			memcpy(this->elements, elements, 4 * 4 * sizeof(float));
		}
		Matrix4::Matrix4(const Matrix4& matrix)
		{
			memcpy(this->elements, matrix.elements, 4 * 4 * sizeof(float));
		}
		Matrix4::Matrix4(const Matrix3& matrix)
		{
			memset(elements, 0, 4 * 4 * sizeof(float));
			elements[0 + 0 * SIZE] = matrix.elements[0 + 0 * (SIZE - 1)];
			elements[0 + 1 * SIZE] = matrix.elements[0 + 1 * (SIZE - 1)];
			elements[0 + 2 * SIZE] = matrix.elements[0 + 2 * (SIZE - 1)];
			elements[1 + 0 * SIZE] = matrix.elements[1 + 0 * (SIZE - 1)];
			elements[1 + 1 * SIZE] = matrix.elements[1 + 1 * (SIZE - 1)];
			elements[1 + 2 * SIZE] = matrix.elements[1 + 2 * (SIZE - 1)];
			elements[2 + 0 * SIZE] = matrix.elements[2 + 0 * (SIZE - 1)];
			elements[2 + 1 * SIZE] = matrix.elements[2 + 1 * (SIZE - 1)];
			elements[2 + 2 * SIZE] = matrix.elements[2 + 2 * (SIZE - 1)];
			elements[3 + 3 * SIZE] = 1;
		}
		Matrix4 Matrix4::Add(const Matrix4& matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] += matrix.elements[i];
			}
			return *this;
		}
		Matrix4 Matrix4::Subtract(const Matrix4& matrix)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] -= matrix.elements[i];
			}
			return *this;
		}
		Matrix4 Matrix4::Multiply(float scalar)
		{
			for (int i = 0; i < SIZE * SIZE; i++) {
				elements[i] *= scalar;
			}
			return *this;
		}
		void Matrix4::clean()
		{
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = Math::cleanFloat(elements[i], DELTA);
			}
		}
		size_t Matrix4::size() {
			return 4 * 4 * sizeof(float);
		}

		Vector4 Matrix4::operator[] (int i) const {
			return Vector4(elements[i * SIZE], elements[(i * SIZE) + 1], elements[(i * SIZE) + 2], elements[(i * SIZE) + 3]);
		}
		Matrix4 operator+(Matrix4 left, Matrix4 right)
		{
			return left.Add(right);
		}
		Matrix4 operator-(Matrix4 left, Matrix4 right)
		{
			return left.Subtract(right);
		}
		Matrix4 operator*(Matrix4 left, float scalar)
		{
			return left.Multiply(scalar);
		}
		Matrix4 operator*(float scalar, Matrix4 left)
		{
			return left.Multiply(scalar);
		}
		Matrix4 operator*(Matrix4 left, Matrix4 right)
		{
			float results[16];
			memset(results, 0, 4 * 4 * sizeof(float));
			for (int row = 0; row < 4; row++) {

				for (int col = 0; col < 4; col++) {

					float sum = 0.0f;

					for (int e = 0; e < 4; e++) {
						sum = sum + (left.elements[row + e * 4] * right.elements[e + col * 4]);
					}

					//std::cout << "[ "<< row << col << " ] =" <<sum << std::endl;
					results[row + col * 4] = sum;
				}
			}
			return Matrix4(results);
		}
		Vector4 operator*(Vector4 vector, Matrix4 matrix)
		{
			float mx, my, mz, mw;
			mx = vector.x * matrix.elements[0 + 0 * 4] + vector.y * matrix.elements[1 + 0 * 4] + vector.z * matrix.elements[2 + 0 * 4] + vector.w * matrix.elements[3 + 0 * 4];
			my = vector.x * matrix.elements[0 + 1 * 4] + vector.y * matrix.elements[1 + 1 * 4] + vector.z * matrix.elements[2 + 1 * 4] + vector.w * matrix.elements[3 + 1 * 4];
			mz = vector.x * matrix.elements[0 + 2 * 4] + vector.y * matrix.elements[1 + 2 * 4] + vector.z * matrix.elements[2 + 2 * 4] + vector.w * matrix.elements[3 + 2 * 4];
			mw = vector.x * matrix.elements[0 + 3 * 4] + vector.y * matrix.elements[1 + 3 * 4] + vector.z * matrix.elements[2 + 3 * 4] + vector.w * matrix.elements[3 + 3 * 4];
			return Vector4(mx, my, mz, mw);
		}
		Vector4 operator*(Matrix4 matrix, Vector4 vector)
		{
			float x = matrix.elements[0] * vector.x + matrix.elements[4] * vector.y + matrix.elements[8] * vector.z + matrix.elements[12] * vector.w;
			float y = matrix.elements[1] * vector.x + matrix.elements[5] * vector.y + matrix.elements[9] * vector.z + matrix.elements[13] * vector.w;
			float z = matrix.elements[2] * vector.x + matrix.elements[6] * vector.y + matrix.elements[10] * vector.z + +matrix.elements[14] * vector.w;
			float w = matrix.elements[3] * vector.x + matrix.elements[7] * vector.y + matrix.elements[11] * vector.z + +matrix.elements[15] * vector.w;
			return Vector4(x, y, z, w);
		}
		bool Matrix4::operator==(const Matrix4& matrix)
		{
			bool eq = true;
			for (int r = 0; r < SIZE; r++) {
				for (int c = 0; c < SIZE; c++) {
					if (fabs(elements[r + c * SIZE] - matrix.elements[r + c * SIZE]) > DELTA) {
						eq = false;
						break;
					}
				}
			}
			return eq;
		}
		bool Matrix4::operator!=(const Matrix4& matrix)
		{
			return !(*this == matrix);
		}
		float Matrix4::determinant()
		{
			float temp[SIZE];
			float elmentA[] = { elements[5],elements[6],elements[7],elements[9],elements[10],elements[11],elements[13],elements[14],elements[15] };
			Matrix3 a = Matrix3(elmentA);
			float elmentB[] = { elements[1],elements[2],elements[3],elements[9],elements[10],elements[11],elements[13],elements[14],elements[15] };
			Matrix3 b = Matrix3(elmentB);
			float elmentC[] = { elements[1],elements[2],elements[3],elements[5],elements[6],elements[7],elements[13],elements[14],elements[15] };
			Matrix3 c = Matrix3(elmentC);
			float elmentD[] = { elements[1],elements[2],elements[3],elements[5],elements[6],elements[7],elements[9],elements[10],elements[11] };
			Matrix3 d = Matrix3(elmentD);
			temp[0] = a.determinant();
			temp[1] = -b.determinant();
			temp[2] = c.determinant();
			temp[3] = -d.determinant();
			return elements[0] * temp[0] + elements[4] * temp[1] + elements[8] * temp[2] + elements[12] * temp[3];
		}
		Matrix4 Matrix4::transpose()
		{
			return Matrix4(
				Vector4((*this).cols[0].x, (*this).cols[1].x, (*this).cols[2].x, (*this).cols[3].x),
				Vector4((*this).cols[0].y, (*this).cols[1].y, (*this).cols[2].y, (*this).cols[3].y),
				Vector4((*this).cols[0].z, (*this).cols[1].z, (*this).cols[2].z, (*this).cols[3].z),
				Vector4((*this).cols[0].w, (*this).cols[1].w, (*this).cols[2].w, (*this).cols[3].w)
			);
		}
		Matrix4 Matrix4::adjugate()
		{
			Matrix4 adj = (*this);
			adj.elements[1 + 0 * 4] = -adj.elements[1 + 0 * 4];
			return adj;
		}
		std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix)
		{
			stream << "[" << matrix.elements[0 + 0 * 4] << " " << matrix.elements[0 + 1 * 4] << " " << matrix.elements[0 + 2 * 4] << " " << matrix.elements[0 + 3 * 4] << "]" << std::endl;
			stream << "[" << matrix.elements[1 + 0 * 4] << " " << matrix.elements[1 + 1 * 4] << " " << matrix.elements[1 + 2 * 4] << " " << matrix.elements[1 + 3 * 4] << "]" << std::endl;
			stream << "[" << matrix.elements[2 + 0 * 4] << " " << matrix.elements[2 + 1 * 4] << " " << matrix.elements[2 + 2 * 4] << " " << matrix.elements[2 + 3 * 4] << "]" << std::endl;
			stream << "[" << matrix.elements[3 + 0 * 4] << " " << matrix.elements[3 + 1 * 4] << " " << matrix.elements[3 + 2 * 4] << " " << matrix.elements[3 + 3 * 4] << "]" << std::endl;
			return stream;
		}

		/*************** Matrix Factory  ******************/

		Matrix2 MatrixFactory::Identity2()
		{
			return Matrix2(1);
		}
		Matrix2 MatrixFactory::Rotate2(const float& angle)
		{
			float a = Math::angleToRad(angle);
			float cos_ang = (float)cos(a);
			float sin_ang = (float)sin(a);
			Matrix2 rot = Matrix2();
			rot.elements[0 + 0 * rot.SIZE] = cos_ang;
			rot.elements[1 + 0 * rot.SIZE] = sin_ang;
			rot.elements[0 + 1 * rot.SIZE] = -sin_ang;
			rot.elements[1 + 1 * rot.SIZE] = cos_ang;
			return rot;
		}
		Matrix2 MatrixFactory::Scale2(const float& x, const float& y)
		{
			Matrix2 scl = Matrix2();
			scl.elements[0 + 0 * scl.SIZE] = x;
			scl.elements[1 + 1 * scl.SIZE] = y;
			return scl;
		}
		Matrix3 MatrixFactory::Translate2(const float& x, const float& y)
		{
			Matrix3 trans = Matrix3(1);
			trans.cols[1] = Vector4(x, y, 1);
			return trans;
		}
		Matrix3 MatrixFactory::Identity3()
		{
			return Matrix3(1);
		}
		Matrix3 MatrixFactory::DualMatrix(const Vector3& vector)
		{
			Matrix3 dual = Matrix3();
			dual.elements[1 + 0 * 3] = vector.z;
			dual.elements[2 + 0 * 3] = -vector.y;
			dual.elements[0 + 1 * 3] = -vector.z;
			dual.elements[2 + 1 * 3] = vector.x;
			dual.elements[0 + 2 * 3] = vector.y;
			dual.elements[1 + 2 * 3] = -vector.x;
			return dual;
		}
		Matrix3 MatrixFactory::Rotate3(const float& angle, const Vector3& axis)
		{
			Matrix3 rot = Matrix3(1);
			float a = Math::angleToRad(angle);
			float cos_ang = (float)cos(a);
			float sin_ang = (float)sin(a);
			if (axis == Vector3(0, 0, 1)) {
				rot.elements[0 + 0 * 3] = cos_ang;
				rot.elements[1 + 0 * 3] = sin_ang;
				rot.elements[0 + 1 * 3] = -sin_ang;
				rot.elements[1 + 1 * 3] = cos_ang;
			}
			if (axis == Vector3(0, 1, 0)) {
				rot.elements[0 + 0 * 3] = cos_ang;
				rot.elements[2 + 0 * 3] = -sin_ang;
				rot.elements[0 + 2 * 3] = sin_ang;
				rot.elements[2 + 2 * 3] = cos_ang;
			}
			if (axis == Vector3(1, 0, 0)) {
				rot.elements[1 + 1 * 3] = cos_ang;
				rot.elements[2 + 1 * 3] = sin_ang;
				rot.elements[1 + 2 * 3] = -sin_ang;
				rot.elements[2 + 2 * 3] = cos_ang;
			}
			return rot;
		}
		Matrix3 MatrixFactory::Scale3(const float& x, const float& y, const float& z)
		{
			Matrix3 scl = Matrix3();
			scl.elements[0 + 0 * scl.SIZE] = x;
			scl.elements[1 + 1 * scl.SIZE] = y;
			scl.elements[2 + 2 * scl.SIZE] = z;
			return scl;
		}
		Matrix3 MatrixFactory::Translate3(const float& x, const float& y, const float& z)
		{
			Matrix3 trans = Matrix3(1);
			trans.cols[2] = Vector3(x, y, z);
			return trans;
		}
		Matrix3 MatrixFactory::Rodrigues3(const Vector3& axis, const float& angle)
		{
			float a = Math::angleToRad(angle);
			float cos_ang = (float)cos(a);
			float sin_ang = (float)sin(a);
			Matrix3 dual = DualMatrix(axis);
			Matrix3 id = Identity3();
			return id + (sin_ang * (dual)) + ((1 - cos_ang) * (dual * dual));
		}
		Matrix4 MatrixFactory::Rodrigues4(const Vector3& axis, const float& angle)
		{
			return Matrix4(Rodrigues3(axis, angle));
		}
		Matrix4 MatrixFactory::Identity4()
		{
			return Matrix4(1);
		}
		Matrix4 MatrixFactory::Translate(const float& x, const float& y, const float& z)
		{
			Matrix4 trans = Matrix4(1);
			trans.cols[3] = Vector4(x, y, z, 1);
			return trans;
		}
		Matrix4 MatrixFactory::Translate(const Vector3& pos)
		{
			return Translate(pos.x, pos.y, pos.z);
		}
		Matrix4 MatrixFactory::Rotate(const float& angle, const Vector3& axis)
		{
			Matrix3 rot = Rotate3(angle, axis);
			return Matrix4(rot);
		}
		Matrix4 MatrixFactory::RotateX(const float& angle)
		{
			return Rotate(angle, Vector3(1, 0, 0));
		}
		Matrix4 MatrixFactory::RotateY(const float& angle)
		{
			return Rotate(angle, Vector3(0, 1, 0));
		}
		Matrix4 MatrixFactory::Scale(const float& x, const float& y, const float& z)
		{
			return  Matrix4(Scale3(x, y, z));
		}
		Matrix4 MatrixFactory::Scale(const Vector3& scale)
		{
			return  Scale(scale.x, scale.y, scale.z);
		}
}