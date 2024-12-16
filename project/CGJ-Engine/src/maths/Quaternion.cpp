#include "maths/Quaternion.h"
#include "Utils.h"

namespace engine {

	/**
	* For all implementations in this file, @see Quaternion.h for details
	*/

	Quaternion::operator const Vector4() const {
		return Vector4(x, y, z, t);
	}

	Quaternion::operator const Matrix4() const {
		
		Matrix4 *m = new Matrix4(t), *m2 = new Matrix4(t);

		m->cols[0].y = -z; m->cols[0].z = y; m->cols[0].w = -x;
		m->cols[1].x = z; m->cols[1].z = -x; m->cols[1].w = -y;
		m->cols[2].x = -y; m->cols[2].y = x; m->cols[2].w = -z;
		m->cols[3].x = x; m->cols[3].y = y; m->cols[3].z = z;

		m2->cols[0].y = -z; m2->cols[0].z = y; m2->cols[0].w = x;
		m2->cols[1].x = z; m2->cols[1].z = -x; m2->cols[1].w = y;
		m2->cols[2].x = -y; m2->cols[2].y = x; m2->cols[2].w = z;
		m2->cols[3].x = -x; m2->cols[3].y = -y; m2->cols[3].z = -z;

		return *m * *m2;

		/*float n = pow(length(), 2);
		float s = n == 0 ? 0 : 2 / n;
		float tx = s * t * x, ty = s * t * y, tz = s * t * z;
		float xx = s * x * x, xy = s * x * y, xz = s * x * z;
		float yy = s * y * y, yz = s * y * z, zz = s * z * z;

		Matrix4* m = new Matrix4(1);
		m->cols[0] = Vector4(1.0f - (yy + zz), xy - tz, xz + ty, 0.0f);
		m->cols[1] = Vector4(xy + tz, 1.0f - (xx + zz), yz - tx, 0.0f);
		m->cols[2] = Vector4(xz - ty, yz + tx, 1.0f - (xx + yy), 0.0f);

		//m->clean();

		return *m;*/
	}

	void Quaternion::operator = (const Quaternion q) {
		x = q.x;
		y = q.y;
		z = q.z;
		t = q.t;
	}

	bool Quaternion::operator == (const Quaternion q) const {
		return (fabs(t - q.t) < threshold && fabs(x - q.x) < threshold &&
			fabs(y - q.y) < threshold && fabs(z - q.z) < threshold);
	}

	bool Quaternion::operator != (const Quaternion q) const {
		return !((*this) == q);
	}

	const Quaternion operator+ (const Quaternion left, const Quaternion right) {
		Quaternion q = left;
		return q += right;
	}

	const Quaternion Quaternion::operator+= (const Quaternion q) {
		x += q.x;
		y += q.y;
		z += q.z;
		t += q.t;
		return (*this);
	}

	const Quaternion operator* (const Quaternion quaternion, const float scalar) {
		Quaternion q = quaternion;
		return q *= scalar;
	}

	const Quaternion Quaternion::operator*= (const float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		t *= scalar;
		return (*this);
	}

	const Quaternion operator* (const Quaternion left, const Quaternion right) {
		Quaternion q = left;
		return q *= right;
	}

	const Quaternion Quaternion::operator*= (const Quaternion q) {
		t = t * q.t - x * q.x - y * q.y - z * q.z;
		x = t * q.x + x * q.t + y * q.z - z * q.y;
		y = t * q.y + y * q.t + z * q.x - x * q.z;
		z = t * q.z + z * q.t + x * q.y - y * q.x;
		return (*this);
	}

	const float Quaternion::getThreshold() const {
		return threshold;
	}

	const Quaternion Quaternion::fromAngleAxis(const float theta, const Vector3 axis) {
		Vector3 axisn = axis.normalize();

		Quaternion q;
		q.t = Math::cosine(theta / 2);
		float s = Math::sine(theta / 2);
		q.x = axisn.x * s;
		q.y = axisn.y * s;
		q.z = axisn.z * s;
		q.clean();

		return (*new Quaternion(q.normalize()));
	}

	void Quaternion::toAngleAxis(float& theta, Vector3& axis) const {
		Quaternion qn = normalize();
		theta = Math::radToAngle(2.0f * acos(qn.t));
		float s = sqrt(1.0f - qn.t * qn.t);
		if (s < threshold) {
			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
		}
		else {
			float sinv = 1 / s;
			axis.x = qn.x * sinv;
			axis.y = qn.y * sinv;
			axis.z = qn.z * sinv;
		}
	}

	const float Quaternion::length() const {
		return Math::cleanFloat(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(t, 2)), threshold);
	}

	const Quaternion Quaternion::normalize() const {
		Quaternion q = (*new Quaternion(*this));
		float s = 1.0f / this->length();
		q = q * s;
		return (*new Quaternion(*this));
	}

	const Quaternion Quaternion::conjugate() const {
		Quaternion conjugate = { t, -x, -y, -z };
		return (*new Quaternion(conjugate));
	}

	const Quaternion Quaternion::inverse() const {
		Quaternion q = (conjugate() * (1.0f / length()));
		q.clean();
		return (*new Quaternion(q));
	}

	const Quaternion Quaternion::lerp(const Quaternion q, const float k) const {
		float cos_angle = x * q.x + y * q.y + z * q.z + t * q.t;
		float k0 = 1.0f - k;
		float k1 = (cos_angle > 0) ? k : -k;
		Quaternion qf;
		Quaternion qi = (*new Quaternion(*this));
		qi = qi * Math::cleanFloat(k0, threshold);
		qf = qi + (q * Math::cleanFloat(k1, threshold));
		return (*new Quaternion(qf.normalize()));
	}

	const Quaternion Quaternion::slerp(const Quaternion q, const float k) const {
		float angle = acos(x * q.x + y * q.y + z * q.z + t * q.t);
		float k0 = sin((1 - k) * angle) / sin(angle);
		float k1 = sin(k * angle) / sin(angle);
		Quaternion qi = (*new Quaternion(*this));
		qi *= k0;
		qi += q * k1;
		return (*new Quaternion(qi.normalize()));
	}

	void Quaternion::clean() {
		x = Math::cleanFloat(x, threshold);
		y = Math::cleanFloat(y, threshold);
		z = Math::cleanFloat(z, threshold);
		t = Math::cleanFloat(t, threshold);
	}

	void Quaternion::printAngleAxis(const std::string& s) const {
		std::cout << s << " = [" << std::endl;

		float thetaf;
		Vector3 axisf;
		toAngleAxis(thetaf, axisf);
		std::cout << "  angle = " << thetaf << std::endl;
		std::cout << "  axis  = " << axisf << std::endl;
		std::cout << "]" << std::endl;
	}

	std::ostream& operator << (std::ostream& out, const Quaternion q) {
		out << " = (" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
		return out;
	}

	std::istream& operator >> (std::istream& in, Quaternion& q) {
		float t;
		std::cout << "T: ";
		in >> t;
		q.t = t;
		operator>> (in, (Vector3&)q);
		return in;
	}

}