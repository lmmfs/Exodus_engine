#pragma once
#include <string>

#include "Vector.h"
#include "Matrix.h"

namespace engine {

	/**
	* Quaternion class
	*
	* For other members not represented here, @see Vector.h#Vector4 for details
	*/
	class Quaternion {

	private:

		float x = 0.0f, y = 0.0f, z = 0.0f, t = 1.0f;

		/**
		* The threshold used to clean the values
		*/
		const float threshold = (float)1.0e-5;

		//////////////////
		// Constructors //
		//////////////////

	public:

		Quaternion() {};
		Quaternion(const float k) {
			x = y = z = k;
		};
		Quaternion(const float t, const float x, const float y, const float z) : t(t), x(x), y(y), z(z) {};
		Quaternion(const Vector4 vec4) : t(vec4.w), x(vec4.x), y(vec4.y), z(vec4.z) {};

		///////////
		// Casts //
		///////////

	public:

		/**
		* Casts this quaternion to a vec4
		*/
		operator const Vector4() const;

		/**
		* Casts this quaternion to a mat4
		*/
		operator const Matrix4() const;

		////////////////
		// Assignment //
		////////////////

	public:

		/**
		* Sets the coords of this quaternion to the given quaternion
		*
		* @param Quaternion the quaternion to copy
		*/
		void operator = (const Quaternion);

		////////////////
		// Comparison //
		////////////////

		/**
		* Checks this quaternion with the given one for equality
		*
		* @return true if both quaternions are equal, false otherwise
		*/
		bool operator == (const Quaternion) const;

		/**
		* Checks this quaternion with the given one for difference
		*
		* @return true if the quaternions are different, false otherwise
		*/
		bool operator != (const Quaternion) const;

		//////////////
		// Addition //
		//////////////

	public:

		/**
		* Calculates adding the quaternion with a given quaternion
		*
		* @param Quaternion the quaternion to add
		* @return the result of the addition
		*/
		friend const Quaternion operator+ (const Quaternion, const Quaternion);

		/**
		* Adds the given quaternion to this quaternion
		*
		* @param Quaternion the quaternion to add
		* @return the result of the addition
		*/
		const Quaternion operator+= (const Quaternion);

		////////////////////
		// Multiplication //
		////////////////////

	public:

		/**
		* Calculates multiplying the quaternion with a scalar
		*
		* @param float the scalar to multiply
		* @return the result of the multiplication
		*/
		friend const Quaternion operator* (const Quaternion, const float);

		/**
		* Calculates multiplying the quaternion with a scalar
		*
		* @param float the scalar to multiply
		* @return the result of the multiplication
		*/
		friend const Quaternion operator* (const float, const Quaternion);

		/**
		* Multiplies the quaternion with a scalar
		*
		* @param float the scalar to multiply
		* @return the result of the multiplication
		*/
		const Quaternion operator*= (const float);

		/**
		* Calculates multiplying the quaternion with a given quaternion
		*
		* @param Quaternion the quaternion to multiply
		* @return the result of the multiplication
		*/
		friend const Quaternion operator* (const Quaternion, const Quaternion);

		/**
		* Multiplies the quaternion with a given quaternion
		*
		* @param Quaternion the quaternion to multiply
		* @return the result of the multiplication
		*/
		const Quaternion operator*= (const Quaternion);

		///////////////
		// Utilities //
		///////////////

	public:

		/**
		* Returns the cleanse threshold
		*/
		const float getThreshold() const;

		/**
		* Creates a quaternion from an angle and a rotation axis
		*
		* @param float the angle
		* @param vec4 the rotation axis
		* @return the Quaternion
		*/
		static const Quaternion fromAngleAxis(const float, const Vector3);

		/**
		* Returns this quaternion in the form of angle and rotation axis
		*
		* @param float& the float reference to store the angle
		* @param vec4& the vec4 reference to store the rotation axis
		*/
		void toAngleAxis(float&, Vector3&) const;

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Calculates the length (or norm) of the quaternion
		*
		* @return the length of the quaternion
		*/
		const float length() const;

		/**
		* Calculates the normalization of the quaternion
		*
		* @return the quaternion normalized
		*/
		const Quaternion normalize() const;

		/**
		* Calculates the conjugate of the quaternion
		*
		* @return the quaternion conjugated
		*/
		const Quaternion conjugate() const;

		/**
		* Calculates the inverse of the quaternion
		*
		* @return the quaternion inversed
		*/
		const Quaternion inverse() const;

		/**
		* Calculates the linear interpolation of the quaternion
		* with the given quaternion and angles of rotation
		*
		* @return the calculation of the lerp
		*/
		const Quaternion lerp(const Quaternion, const float) const;

		/**
		* Calculates the spherical linear interpolation of the
		* quaternion with the given quaternion and angles of rotation
		*
		* @return the calculation of the lerp
		*/
		const Quaternion slerp(const Quaternion, const float) const;

		/**
		* Cleans this quaternion's coordinates, setting the values
		* with a threshold bias
		*/
		void clean();

		/////////////
		// Streams //
		/////////////

	public:

		/**
		* Prints the quaternion in the form of angle and rotation axis
		*
		* @param string the string that will prepend the angle and axis info
		*/
		void printAngleAxis(const std::string&) const;

		/**
		* Writes the given quaternion in human readable form to the given stream
		*
		* @param ostream the output stream
		* @param Quaternion the quaternion to write
		* @return ostream the stream after writing
		*/
		friend std::ostream& operator << (std::ostream&, const Quaternion);

		/**
		* Reads values from an input stream to create a quaternion
		*
		* @param istream the input stream
		* @param Quaternion the quaternion reference to create
		* @return istream the stream after reading
		*/
		friend std::istream& operator >> (std::istream&, Quaternion&);

	};

}