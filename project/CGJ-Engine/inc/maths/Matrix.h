#pragma once

#include<iostream>
#include <cmath>
#include "Vector.h"


namespace engine {

	class Matrix2;
	class Matrix3;
	class Matrix4;

	/**
	* 2x2 Matrix Class
	*/
	class Matrix2 {

	protected:

		/**
		* Addition auxiliary method
		* 
		* @param matrix the matrix to add
		* @return the result of adding this matrix to the given matrix
		*/
		Matrix2 Add(const Matrix2 matrix);

		/**
		* Subtraction auxiliary method
		*
		* @param matrix the matrix to subtract
		* @return the result of subtracting the given matrix from this matrix
		*/
		Matrix2 Subtract(const Matrix2 matrix);

		/**
		* Multiplication auxiliary method
		*
		* @param matrix the matrix to multiply
		* @return the result of multiplying this matrix with the given matrix
		*/
		Matrix2 Multiply(const Matrix2 matrix);

		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this matrix with the given scalar
		*/
		Matrix2 Multiply(float scalar);

	public:

		// Matrix size (2)
		static const int SIZE = 2;

		// Matrix elements
		union
		{
			float elements[SIZE * SIZE];
			Vector2 cols[SIZE];
		};

		//////////////////
		// Constructors //
		//////////////////

	public:

		/**
		* Constructs a 2x2 Matrix
		*/
		Matrix2();

		/**
		* Construct a Matrix with the diagonal elements equal to diagonal
		*
		* @param diagonal the value to place in diagonal elements
		*/
		Matrix2(const float& diagonal);

		/**
		* Construct a Matrix from the given rows
		*
		* @param row0 the first row
		* @param row1 the second row
		*/
		Matrix2(const Vector2& row0, const Vector2& row1);

		/**
		* Construct a Matrix from the given elements
		*
		* @param elements the values to place in the matrix elements
		*/
		Matrix2(float* elements);

		/**
		* Copy a Matrix from another Matrix
		*
		* @param matrix the matrix to copy
		*/
		Matrix2(const Matrix2& matrix);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this matrix to the given matrix for equality
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are equal, false otherwise
		*/
		bool operator==(const Matrix2& matrix);

		/**
		* Compares this matrix to the given matrix for difference
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are different, false otherwise
		*/
		bool operator!=(const Matrix2& matrix);

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the row i of the matrix
		*
		* @param i the index of the row
		* @return the row
		*/
		Vector2 operator[] (int i) const;

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding matrix left with matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of adding the matrices 
		*/
		friend Matrix2 operator+(Matrix2 left, const Matrix2 right);

		/////////////////
		// Subtraction //
		/////////////////

	public:

		/**
		* Calculates subtracting matrix right from matrix left
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of subtracting the matrices
		*/
		friend Matrix2 operator-(Matrix2 left, const Matrix2 right);
		
		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the matrix with the scalar
		*
		* @param matrix the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix2 operator*(Matrix2 matrix, float scalar);
		
		/**
		* Calculates multiplying the matrix with the scalar
		*
		* @param matrix the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix2 operator*(float scalar, Matrix2 matrix);
		
		/**
		* Calculates multiplying the matrix left with the matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of multiplying the matrices
		*/
		friend Matrix2 operator*(Matrix2 left, const Matrix2 right);

		/**
		* Calculates multiplying a Vector with a Matrix
		*
		* @param vector the vector
		* @param matrix the matrix
		* @return the resulting vector of multiplying the vector with the matrix
		*/
		friend Vector2 operator*(Vector2 vector, const Matrix2 matrix);

		/**
		* Calculates multiplying a Matrix with a Vector
		*
		* @param matrix the matrix
		* @param vector the vector
		* @return the resulting vector of multiplying the matrix with the vector
		*/
		friend Vector2 operator*(Matrix2 matrix, Vector2 vector);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates this matrix's transpose
		*
		* @return the matrix transposed
		*/
		Matrix2 transpose();

		/**
		* Calculates this matrix's determinant
		*
		* @return the determinant
		*/
		float determinant();

		/**
		* Calculates this matrix's adjugate
		*
		* @return the matrix adjugated
		*/
		Matrix2 adjugate();

		/**
		* Calculates this matrix's inverse
		*
		* @return the matrix inverted
		*/
		Matrix2 inverse();

		/**
		* Gets this matrix's size
		*
		* @return the size of the matrix (2)
		*/
		static size_t size();

		/**
		* Cleans this matrix's elements, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the matrix to the stream
		*
		* @param stream the stream
		* @param matrix the matrix
		* @return the stream after printing the matrix
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Matrix2& matrix);

	};


	/**
	* 3x3 Matrix Class
	*/
	class Matrix3
	{

	protected:

		/**
		* Addition auxiliary method
		*
		* @param matrix the matrix to add
		* @return the result of adding this matrix to the given matrix
		*/
		Matrix3 Add(const Matrix3& matrix);

		/**
		* Subtraction auxiliary method
		*
		* @param matrix the matrix to subtract
		* @return the result of subtracting the given matrix from this matrix
		*/
		Matrix3 Subtract(const Matrix3& matrix);
		
		/**
		* Multiplication auxiliary method
		*
		* @param matrix the matrix to multiply
		* @return the result of multiplying this matrix with the given matrix
		*/
		Matrix3 Multiply(const Matrix3& matrix);
		
		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this matrix with the given scalar
		*/
		Matrix3 Multiply(float scalar);

	public:

		// Matrix size (3)
		static const int SIZE = 3;

		// Matrix elements
		union
		{
			float elements[SIZE * SIZE];
			Vector3 cols[SIZE];
		};

		//////////////////
		// Constructors //
		//////////////////

	public:

		/**
		* Construct a 3x3 Matrix
		*/
		Matrix3();

		/**
		* Construct a Matrix with the diagonal elements equal to diagonal
		*
		* @param diagonal the value to place in diagonal elements
		*/
		Matrix3(const float& diagonal);

		/**
		* Construct a Matrix from the given columns
		*
		* @param col0 the first column
		* @param col1 the second column
		* @param col2 the third column
		*/
		Matrix3(const Vector3& col0, const Vector3& col1, const Vector3& col2);

		/**
		* Construct a Matrix from the given elements
		*
		* @param elements the values to place in the matrix elements
		*/
		Matrix3(float* elements);

		/**
		* Submatrix a 4x4 Matrix to a 3x3 Matrix
		*
		* @param matrix the matrix to submatrix
		*/
		Matrix3(const Matrix4& matrix);

		/**
		* Copy a Matrix from another Matrix
		*
		* @param matrix the matrix to copy
		*/
		Matrix3(const Matrix3& matrix);

		/**
		* Supermatrix a 2x2 Matrix to a 3x3 Matrix
		*
		* @param matrix the matrix to supermatrix
		*/
		Matrix3(const Matrix2& matrix);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this matrix to the given matrix for equality
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are equal, false otherwise
		*/
		bool operator==(const Matrix3& matrix);

		/**
		* Compares this matrix to the given matrix for difference
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are different, false otherwise
		*/
		bool operator!=(const Matrix3& matrix);

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the row i of the matrix
		*
		* @param i the index of the row
		* @return the row
		*/
		Vector3 operator[] (int i) const;

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding matrix left with matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of adding the matrices
		*/
		friend Matrix3 operator+(Matrix3 left, const Matrix3 right);

		/////////////////
		// Subtraction //
		/////////////////

	public:

		/**
		* Calculates subtracting matrix right from matrix left
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of subtracting the matrices
		*/
		friend Matrix3 operator-(Matrix3 left, const Matrix3 right);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the matrix with the scalar
		*
		* @param matrix the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix3 operator*(Matrix3 matrix, float scalar);

		/**
		* Calculates multiplying the matrix matrix with the scalar
		*
		* @param matrix the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix3 operator*(float scalar, Matrix3 matrix);

		/**
		* Calculates multiplying the matrix left with the matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of multiplying the matrices
		*/
		friend Matrix3 operator*(Matrix3 left, const Matrix3 right);

		/**
		* Calculates multiplying a Vector with a Matrix
		*
		* @param vector the vector
		* @param matrix the matrix
		* @return the resulting vector of multiplying the vector with the matrix
		*/
		friend Vector3 operator*(Vector3 vector, const Matrix3 matrix);

		/**
		* Calculates multiplying a Matrix with a Vector
		*
		* @param matrix the matrix
		* @param vector the vector
		* @return the resulting vector of multiplying the matrix with the vector
		*/
		friend Vector3 operator*(Matrix3 matrix, Vector3 vector);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates this matrix's transpose
		*
		* @return the matrix transposed
		*/
		Matrix3 transpose();

		/**
		* Calculates this matrix's determinant
		*
		* @return the determinant
		*/
		float determinant();

		/**
		* Calculates this matrix's adjugate
		*
		* @return the matrix adjugated
		*/
		Matrix3 adjugate();

		/**
		* Calculates this matrix's inverse
		*
		* @return the matrix inverted
		*/
		Matrix3 inverse();

		/**
		* Calculates the cofactors matrix
		*
		* @return the matrix cofactors
		*/
		Matrix3 cofactors();

		/**
		* Gets this matrix's size
		*
		* @return the size of the matrix (3)
		*/
		static size_t size();

		/**
		* Cleans this matrix's elements, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the matrix to the stream
		*
		* @param stream the stream
		* @param matrix the matrix
		* @return the stream after printing the matrix
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Matrix3& matrix);

	};

	/**
	* 4x4 Matrix Class
	*/
	class Matrix4
	{

	protected:

		/**
		* Addition auxiliary method
		*
		* @param matrix the matrix to add
		* @return the result of adding this matrix to the given matrix
		*/
		Matrix4 Add(const Matrix4& matrix);

		/**
		* Subtraction auxiliary method
		*
		* @param matrix the matrix to subtract
		* @return the result of subtracting the given matrix from this matrix
		*/
		Matrix4 Subtract(const Matrix4& matrix);

		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this matrix with the given scalar
		*/
		Matrix4 Multiply(float scalar);

	public:

		// Matrix size (4)
		static const int SIZE = 4;

		// Matrix elements
		union
		{
			float elements[SIZE * SIZE];
			Vector4 cols[SIZE];
		};

		//////////////////
		// Constructors //
		//////////////////
		
	public:
		
		/**
		* Construct a 4x4 Matrix
		*/
		Matrix4();

		/**
		* Construct a Matrix with the diagonal elements equal to diagonal
		*
		* @param diagonal the value to place in diagonal elements
		*/
		Matrix4(const float& diagonal);

		/**
		* Construct a Matrix from the given columns
		*
		* @param col0 the first column
		* @param col1 the second column
		* @param col2 the third column
		* @param col3 the fourth column
		*/
		Matrix4(const Vector4& col0, const Vector4& col1, const Vector4& col2, const Vector4& col3);

		/**
		* Construct a Matrix from the given elements
		*
		* @param elements the values to place in the matrix elements
		*/
		Matrix4(float* elements);

		/**
		* Copy a Matrix from another Matrix
		*
		* @param matrix the matrix to copy
		*/
		Matrix4(const Matrix4& matrix);

		/**
		* Supermatrix a 3x3 Matrix to a 4x4 Matrix
		*
		* @param matrix the matrix to supermatrix
		*/
		Matrix4(const Matrix3& matrix);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this matrix to the given matrix for equality
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are equal, false otherwise
		*/
		bool operator==(const Matrix4& matrix);

		/**
		* Compares this matrix to the given matrix for difference
		*
		* @param matrix the matrix to compare
		* @return true if the matrices are different, false otherwise
		*/
		bool operator!=(const Matrix4& matrix);

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the row i of the matrix
		*
		* @param i the index of the row
		* @return the row
		*/
		Vector4 operator[] (int i) const;

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding matrix left with matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of adding the matrices
		*/
		friend Matrix4 operator+(Matrix4 left, const Matrix4 right);

		/////////////////
		// Subtraction //
		/////////////////

	public:

		/**
		* Calculates subtracting matrix right from matrix left
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of subtracting the matrices
		*/
		friend Matrix4 operator-(Matrix4 left, const Matrix4 right);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the matrix with the scalar
		*
		* @param left the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix4 operator*(Matrix4 matrix, float scalar);

		/**
		* Calculates multiplying the matrix with the scalar
		*
		* @param left the matrix to multiply
		* @param scalar the scalar
		* @return the resulting matrix of multiplying the matrix with the scalar
		*/
		friend Matrix4 operator*(float scalar, Matrix4 matrix);

		/**
		* Calculates multiplying the matrix left with the matrix right
		*
		* @param left the first matrix
		* @param right the second matrix
		* @return the resulting matrix of multiplying the matrices
		*/
		friend Matrix4 operator*(Matrix4 left, const Matrix4 right);

		/**
		* Calculates multiplying a Vector with a Matrix
		*
		* @param vector the vector
		* @param matrix the matrix
		* @return the resulting vector of multiplying the vector with the matrix
		*/
		friend Vector4 operator*(Vector4 vector, const Matrix4 matrix);

		/**
		* Calculates multiplying a Matrix with a Vector
		*
		* @param matrix the matrix
		* @param vector the vector
		* @return the resulting vector of multiplying the matrix with the vector
		*/
		friend Vector4 operator*(Matrix4 matrix, Vector4 vector);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates this matrix's transpose
		*
		* @return the matrix transposed
		*/
		Matrix4 transpose();

		/**
		* Calculates this matrix's determinant
		*
		* @return the determinant
		*/
		float determinant();

		/**
		* Calculates this matrix's adjugate
		*
		* @return the matrix adjugated
		*/
		Matrix4 adjugate();

		/**
		* Gets this matrix's size
		*
		* @return the size of the matrix (4)
		*/
		static size_t size();

		/**
		* Cleans this matrix's elements, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the matrix to the stream
		*
		* @param stream the stream
		* @param matrix the matrix
		* @return the stream after printing the matrix
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Matrix4& matrix);
	};

	/**
	* Matrix Factory Utility Class
	*
	* Static methods to create common Matrices
	*/
	class MatrixFactory
	{

	public:

		// Identity Matrix 2x2
		static Matrix2 Identity2();
		// Rotation Matrix 2x2
		static Matrix2 Rotate2(const float& angle);
		// Scaling Matrix 2x2
		static Matrix2 Scale2(const float& x, const float& y);
		// Translation Matrix 2x2
		static Matrix3 Translate2(const float& x, const float& y);

		// Identity Matrix 3x3
		static Matrix3 Identity3();
		// Rotation Matrix 3x3
		static Matrix3 Rotate3(const float& angle, const Vector3& axis);
		// Scaling Matrix 3x3
		static Matrix3 Scale3(const float& x, const float& y, const float& z);
		// Translation Matrix 3x3
		static Matrix3 Translate3(const float& x, const float& y, const float& z);
		// Dual Matrix
		static Matrix3 DualMatrix(const Vector3& axis);
		// Rodrigues Rotation Matrix 3x3
		static Matrix3 Rodrigues3(const Vector3& axis, const float& angle);
			
		// Identity Matrix 4x4
		static Matrix4 Identity4();
		// Translation Matrix 4x4
		static Matrix4 Translate(const float& x, const float& y, const float& z);
		// Translation Matrix 4x4
		static Matrix4 Translate(const Vector3& pos);
		// Rotation Matrix 4x4
		static Matrix4 Rotate(const float& angle, const Vector3& axis);
		// Rotation Matrix 4x4
		static Matrix4 RotateX(const float& angle);
		// Rotation Matrix 4x4
		static Matrix4 RotateY(const float& angle);
		// Scaling Matrix 4x4
		static Matrix4 Scale(const float& x, const float& y, const float& z);
		// Scaling Matrix 4x4
		static Matrix4 Scale(const Vector3& scale);
		// Rodrigues Rotation Matrix 4x4
		static Matrix4 Rodrigues4(const Vector3& axis, const float& angle);

	};

	
}

