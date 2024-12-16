#pragma once

#include<iostream>
#include <cmath>

namespace engine {

	class Vector2;
	class Vector3;
	class Vector4;

	/**
	* Vector of 2 coordinates Class
	*/
	class Vector2
	{

	protected:

		/**
		* Addition auxiliary method
		*
		* @param vector the vector to add
		* @return the result of adding this vector to the given vector
		*/
		Vector2 Add(const Vector2 vector);

		/**
		* Subtraction auxiliary method
		*
		* @param vector the vector to subtract
		* @return the result of subtracting the given vector from this vector
		*/
		Vector2 Subtract(const Vector2 vector);
			
		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this vector with the given scalar
		*/
		Vector2 Multiply(float scalar);

	public:

		// X and Y coordinates
		float x, y;

		//////////////////
		// Constructors //
		//////////////////

	public:

		/**
		* Construct a 2 coordinate Vector
		*/
		Vector2();

		/**
		* Construct a 2 coordinate Vector with value scalar for both coord
		*
		* @param scalar the value scalar for both coord
		*/
		Vector2(const float& scalar);

		/**
		* Construct a 2 coordinate Vector with x and y values
		*
		* @param x the value for the X coordinate
		* @param y the value for the Y coordinate
		*/
		Vector2(const float& x, const float& y);

		/**
		* Copy a 2 coordinate Vector from another vector
		*
		* @param vector the vector to copy
		*/
		Vector2(const Vector2& vector);

		/**
		* Subvector a 3 coordinate vector to a 2 coordinate vector
		*
		* @param vector the vector to subvector
		*/
		Vector2(const Vector3& vector);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this vector to the given vector for equality
		*
		* @param vector the vector to compare
		* @return true if the vectors are equal, false otherwise
		*/
		bool operator==(const Vector2 vector) const;

		/**
		* Compares this vector to the given vector for difference
		*
		* @param vector the vector to compare
		* @return true if the vectors are different, false otherwise
		*/
		bool operator!=(const Vector2 vector) const;

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the i coordinate of the vector
		*
		* @param i the index of the coordinate
		* @return the coordinate value
		*/
		float operator[] (int i) const;

		//////////////
		// Symmetry //
		//////////////

	public:

		/**
		* Calculates the symmetric value of the vector
		*
		* @param vector The vector to calculate symmetry
		*/
		friend Vector2 operator-(const Vector2 vector);

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding vector left with vector right
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of adding the vectors
		*/
		friend Vector2 operator+(Vector2 left, const Vector2 right);

		/**
		* Adds the given vector to this vector
		*
		* @param vector the vector
		* @return the resulting vector of adding the vectors
		*/
		Vector2 operator+=(const Vector2 vector);
			
		/////////////////
		// Subtraction //
		/////////////////

	public:
			
		/**
		* Calculates subtracting vector right from vector left
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of subtracting the vectors
		*/
		friend Vector2 operator-(Vector2 left, const Vector2 right);

		/**
		* Subtracts the given vector from this vector
		*
		* @param vector the vector
		* @return the resulting vector of subtracting the vectors
		*/
		Vector2 operator-=(const Vector2 vector);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param vector the vector
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector2 operator*(Vector2 vector, float scalar);

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param scalar the scalar
		* @param vector the vector
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector2 operator*(float scalar, Vector2 vector);

		/**
		* Multiplies the vector with the given scalar
		*
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		Vector2 operator*=(const float scalar);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates the normalization of the vector
		*
		* @return the vector normalized
		*/
		Vector2 normalize() const;

		/**
		* Calculates the length of the vector
		*
		* @return the vector's length
		*/
		float length() const;

		/**
		* Calculates the dot product with the given vector
		*
		* @param vector the vector to dot product with
		* @return the dot product between this vector and the given vector
		*/
		float dot(const Vector2 vector) const;

		/**
		* Cleans this vector's coordinates, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the vector to the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after printing the vector
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector2 vector);

		/**
		* Reads values for the vector coordinates from the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after reading the coordinates for the vector
		*/
		friend std::istream& operator>>(std::istream& stream, Vector2 vector);

	};

	/**
	* Vector of 3 coordinates Class
	*/
	class Vector3 {

	protected:

		/**
		* Addition auxiliary method
		*
		* @param vector the vector to add
		* @return the result of adding this vector to the given vector
		*/
		Vector3 Add(const Vector3 vector);

		/**
		* Subtraction auxiliary method
		*
		* @param vector the vector to subtract
		* @return the result of subtracting the given vector from this vector
		*/
		Vector3 Subtract(const Vector3 vector);

		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this vector with the given scalar
		*/
		Vector3 Multiply(float scalar);

	public:

		// The X, Y and Z coordinates
		float x, y, z;

		//////////////////
		// Constructors //
		//////////////////

	public:

		/**
		* Construct a 3 coordinate Vector
		*/
		Vector3();

		/**
		* Construct a 3 coordinate Vector with value scalar for the coords
		*
		* @param scalar the value scalar for the coords
		*/
		Vector3(const float& scalar);

		/**
		* Construct a 2 coordinate Vector with x, y and z values
		*
		* @param x the value for the X coordinate
		* @param y the value for the Y coordinate
		* @param z the value for the Z coordinate
		*/
		Vector3(const float& x, const float& y, const float& z);

		/**
		* Supervector a 2 coordinate vector to a 3 coordinate vector
		*
		* @param vector the vector to supervector
		*/
		Vector3(const Vector2& vector);

		/**
		* Supervector X and Y coordinates to a 3 coordinate vector
		*
		* @param x the value for the X coordinate
		* @param y the value for the Y coordinate
		*/
		Vector3(const float& x, const float& y);
		Vector3(const Vector3& vector);

		/**
		* Subvector a 4 coordinate vector to a 3 coordinate vector
		*
		* @param vector the vector to subvector
		*/
		Vector3(const Vector4& vector);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this vector to the given vector for equality
		*
		* @param vector the vector to compare
		* @return true if the vectors are equal, false otherwise
		*/
		bool operator==(const Vector3 vector) const;

		/**
		* Compares this vector to the given vector for difference
		*
		* @param vector the vector to compare
		* @return true if the vectors are different, false otherwise
		*/
		bool operator!=(const Vector3 vector) const;

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the i coordinate of the vector
		*
		* @param i the index of the coordinate
		* @return the coordinate value
		*/
		float operator[] (int i) const;

		//////////////
		// Symmetry //
		//////////////

	public:

		/**
		* Calculates the symmetric value of the vector
		*
		* @param vector The vector to calculate symmetry
		*/
		friend Vector3 operator-(const Vector3 vector);

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding vector left with vector right
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of adding the vectors
		*/
		friend Vector3 operator+(Vector3 left, const Vector3 right);

		/**
		* Adds the given vector to this vector
		*
		* @param vector the vector
		* @return the resulting vector of adding the vectors
		*/
		Vector3 operator+=(const Vector3 vector);

		/////////////////
		// Subtraction //
		/////////////////

	public:

		/**
		* Calculates subtracting vector right from vector left
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of subtracting the vectors
		*/
		friend Vector3 operator-(Vector3 left, const Vector3 right);

		/**
		* Subtracts the given vector from this vector
		*
		* @param vector the vector
		* @return the resulting vector of subtracting the vectors
		*/
		Vector3 operator-=(const Vector3 vector);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param vector the vector
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector3 operator*(Vector3 vector, float scalar);

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param scalar the scalar
		* @param vector the vector
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector3 operator*(float scalar, Vector3 vector);

		/**
		* Multiplies the vector with the given scalar
		*
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		Vector3 operator*=(const float scalar);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates the normalization of the vector
		*
		* @return the vector normalized
		*/
		Vector3 normalize() const;

		/**
		* Calculates the length of the vector
		*
		* @return the vector's length
		*/
		float length() const;

		/**
		* Calculates the dot product with the given vector
		*
		* @param vector the vector to dot product with
		* @return the dot product between this vector and the given vector
		*/
		float dot(const Vector3 vector) const;

		/**
		* Calculates the cross product with the given vector
		*
		* @param vector the vector to cross product with
		* @return the cross product between this vector and the given vector
		*/
		Vector3 cross(Vector3 vector) const;

		/**
		* Calculates rotating the vector, using the Rodrigues Rotation Formula
		*
		* @param axis the axis to rotate on
		* @param angle the angle to rotate
		* @return the vector rotated
		*/
		Vector3 rodrigues(Vector3 axis, float angle) const;

		/**
		* Calculates the linear interpolation to the given vector, by
		* t (0-1)
		*
		* @param vector the destination vector
		* @param t the ammount (0-1)
		* @param the resulting vector from the interpolation
		*/
		Vector3 lerp(Vector3 vector, float t);

		/**
		* Calculates the spherical linear interpolation to the given vector, by
		* t (0-1)
		*
		* @param vector the destination vector
		* @param t the ammount (0-1)
		* @param the resulting vector from the interpolation
		*/
		Vector3 sLerp(Vector3 vector, float t);

		/**
		* Cleans this vector's coordinates, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the vector to the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after printing the vector
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector3 vector);

		/**
		* Reads values for the vector coordinates from the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after reading the coordinates for the vector
		*/
		friend std::istream& operator>>(std::istream& stream, Vector3 vector);

	};

	/**
	* Vector of 4 coordinates Class
	*/
	class Vector4 {

	protected:

		/**
		* Addition auxiliary method
		*
		* @param vector the vector to add
		* @return the result of adding this vector to the given vector
		*/
		Vector4 Add(const Vector4 vector);

		/**
		* Subtraction auxiliary method
		*
		* @param vector the vector to subtract
		* @return the result of subtracting the given vector from this vector
		*/
		Vector4 Subtract(const Vector4 vector);

		/**
		* Multiplication auxiliary method
		*
		* @param scalar the scalar to multiply
		* @return the result of multiplying this vector with the given scalar
		*/
		Vector4 Multiply(float scalar);

	public:

		// The X, Y, Z and W coordinates
		float x, y, z, w;

		//////////////////
		// Constructors //
		//////////////////

	public:

		/**
		* Construct a 4 coordinate Vector
		*/
		Vector4();

		/**
		* Construct a 4 coordinate Vector with value scalar for the coords
		*
		* @param scalar the value scalar for the coords
		*/
		Vector4(float scalar);

		/**
		* Supervector x, y and z coordinates to a 4 coordinate Vector
		*
		* @param x the value for the X coordinate
		* @param y the value for the Y coordinate
		* @param z the value for the Z coordinate
		*/
		Vector4(float x, float y, float z);

		/**
		* Construct a 4 coordinate Vector with x, y, z and w values
		*
		* @param x the value for the X coordinate
		* @param y the value for the Y coordinate
		* @param z the value for the Z coordinate
		* @param w the value for the W coordinate
		*/
		Vector4(float x, float y, float z, float w);

		/**
		* Supervector a 2 coordinate vector to a 4 coordinate vector
		*
		* @param vector the vector to supervector
		*/
		Vector4(const Vector2& vector);

		/**
		* Supervector a 3 coordinate vector to a 4 coordinate vector
		*
		* @param vector the vector to supervector
		*/
		Vector4(const Vector3& vector);

		////////////////
		// Comparison //
		////////////////

	public:

		/**
		* Compares this vector to the given vector for equality
		*
		* @param vector the vector to compare
		* @return true if the vectors are equal, false otherwise
		*/
		bool operator==(const Vector4 vector) const;

		/**
		* Compares this vector to the given vector for difference
		*
		* @param vector the vector to compare
		* @return true if the vectors are different, false otherwise
		*/
		bool operator!=(const Vector4 vector) const;

		////////////
		// Access //
		////////////

	public:

		/**
		* Gets the i coordinate of the vector
		*
		* @param i the index of the coordinate
		* @return the coordinate value
		*/
		float operator[] (int i) const;

		//////////////
		// Symmetry //
		//////////////

	public:

		/**
		* Calculates the symmetric value of the vector
		*
		* @param vector The vector to calculate symmetry
		*/
		friend Vector4 operator-(const Vector4 vector);

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding vector left with vector right
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of adding the vectors
		*/
		friend Vector4 operator+(Vector4 left, const Vector4 right);

		/**
		* Adds the given vector to this vector
		*
		* @param vector the vector
		* @return the resulting vector of adding the vectors
		*/
		Vector4 operator+=(const Vector4 vector);

		/////////////////
		// Subtraction //
		/////////////////

	public:

		/**
		* Calculates subtracting vector right from vector left
		*
		* @param left the first vector
		* @param right the second vector
		* @return the resulting vector of subtracting the vectors
		*/
		friend Vector4 operator-(Vector4 left, const Vector4 right);

		/**
		* Subtracts the given vector from this vector
		*
		* @param vector the vector
		* @return the resulting vector of subtracting the vectors
		*/
		Vector4 operator-=(const Vector4 vector);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param vector the vector
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector4 operator*(Vector4 vector, float scalar);

		/**
		* Calculates multiplying the vector with the scalar
		*
		* @param scalar the scalar
		* @param vector the vector
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		friend Vector4 operator*(float scalar, Vector4 vector);

		/**
		* Multiplies the vector with the given scalar
		*
		* @param scalar the scalar
		* @return the resulting vector of multiplying the vector with the scalar
		*/
		Vector4 operator*=(const float scalar);

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates the normalization of the vector
		*
		* @return the vector normalized
		*/
		Vector4 normalize() const;

		/**
		* Calculates the length of the vector
		*
		* @return the vector's length
		*/
		float length() const;

		/**
		* Calculates the dot product with the given vector
		*
		* @param vector the vector to dot product with
		* @return the dot product between this vector and the given vector
		*/
		float dot(const Vector4 vector) const;

		/**
		* Cleans this vector's coordinates, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the vector to the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after printing the vector
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Vector4 vector);

		/**
		* Reads values for the vector coordinates from the stream
		*
		* @param stream the stream
		* @param vector the vector
		* @return the stream after reading the coordinates for the vector
		*/
		friend std::istream& operator>>(std::istream& stream, Vector4 vector);
	};
}

