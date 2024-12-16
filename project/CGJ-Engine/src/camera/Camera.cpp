#include "camera/Camera.h"
using namespace std;

namespace engine {

	Camera::Camera(const GLuint bp) {
		ubo_bp = bp;
		createBufferObject();
	}

	Camera::Camera(const GLuint bp, float left, float right, float top, float bottom, float near, float far, float dist, int winx, int winy) : Camera::Camera(bp) {
		this->l = left;
		this->r = right;
		this->t = top;
		this->b = bottom;
		this->n = near;
		this->f = far;
		this->distance = dist;
		this->eye = Vector3(eye.x, eye.y, eye.z);
		this->aspect = (float) winx / (float) winy;
		this->rx = MatrixFactory::Identity4();
		this->ry = MatrixFactory::Identity4();
		this->orientation = Quaternion();
		//viewMatrix = createViewMatrix(eye, center + eye, up);
		viewMatrix = createViewMatrix2(rx, ry);
		orthographicMatrix = createOrthographicProjectionMatrix(l, r, t, b, n, f);
		perspectiveMatrix = createPerspectiveProjectionMatrix(fov, aspect, n, f);
		ortho = false;
	}

	Camera::~Camera() {
		destroyBufferObject();
	}

	void Camera::updateEye(const char* mov) {
		float Speed = cameraSpeed * deltaTime;
		if (mov == "f") eye += (Speed * center);
		else if (mov == "b") eye -= Speed * center;
		else if (mov == "l") eye -= right * Speed;
		else if (mov == "r") eye += right * Speed;
		else if (mov == "u") eye += worldUp * Speed;
		else if (mov == "d") eye -= worldUp * Speed;

		recalculateMatrices();
	}

	void Camera::updateViewMatrix2(float xoffset, float yoffset) {
		yaw += xoffset * mouseSensitivity;
		pitch += yoffset * mouseSensitivity;

		Matrix4 T = MatrixFactory::Translate(0, 0, -distance);

		if (gLock) {
			rx = Matrix4(MatrixFactory::Rodrigues3(Vector3(1, 0, 0), pitch));
			ry = Matrix4(MatrixFactory::Rodrigues3(Vector3(0, 1, 0), yaw));
			Matrix4 R = rx * ry;
			viewMatrix = T * R;
		}
		else if (!gLock) {
			Quaternion qx = orientation.fromAngleAxis(pitch, Vector4(1.0f, 0.0f, 0.0f));
			Quaternion qy = orientation.fromAngleAxis(yaw, Vector4(0.0f, 1.0f, 0.0f));

			Quaternion qrot;
			qrot = qx * qy * qrot;
			
			Matrix4 qMatrix = qrot;
			viewMatrix = T * qMatrix;
		}
	}

	void Camera::updateProjection() {
		recalculateMatrices();
	}

	void Camera::updateFoV(double xoffset, double yoffset) {
		if (fov >= 1.0f && fov <= 45.0f) fov -= float(yoffset);
		if (fov <= 1.0f) fov = 1.0f;
		if (fov >= 45.0f) fov = 45.0f;

		recalculateMatrices();
	}

	void Camera::updateDirection(float xpos, float ypos) {
		if (first_direction) {
			previous_x = xpos;
			previous_y = ypos;
			first_direction = false;
		}

		float xoffset = xpos - previous_x;
		float yoffset = previous_y - ypos;

		previous_x = xpos;
		previous_y = ypos;

		yaw += xoffset * mouseSensitivity;
		pitch += yoffset * mouseSensitivity;

		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;

		center.x = Math::cosine(yaw) * Math::cosine(pitch);
		center.y = Math::sine(pitch);
		center.z = Math::sine(yaw) * Math::cosine(pitch);
		center = center.normalize();
		right = center.cross(worldUp);
		up = right.cross(center);

		recalculateMatrices();
	}

	void Camera::resetCenter() {
		center = Vector3(0, 0, -1);
		eye = Vector3(5, 5, 5);
	}
	void Camera::toggleGimbalLock() {
		if (gLock) {
			gLock = false;
		} else {
			gLock = true;
		}
	}

	void Camera::setDelta(float delta) {
		deltaTime = delta;
	}

	void Camera::recalculateMatrices() {
		viewMatrix = createViewMatrix(eye, eye + center, up);
		perspectiveMatrix = createPerspectiveProjectionMatrix(fov, aspect, n, f);
	}

	Matrix4 Camera::createViewMatrix(Vector3 eye, Vector3 center, Vector3 up) {
		Vector3 view = center - eye;
		Vector3 v = view.normalize();
		Vector3 side = v.cross(up);
		Vector3 s = side.normalize();
		Vector3 u = s.cross(v);
		Matrix4 rot = rotateViewMatrix(s, u, v);
		Matrix4 trans = MatrixFactory::Translate(-eye.x, -eye.y, -eye.z);
		Matrix4 viewMatrix = rot * trans;
		return viewMatrix;
	}

	Matrix4 Camera::createViewMatrix2(Matrix4 rx, Matrix4 ry) {
		Matrix4 R = rx * ry;
		Matrix4 T = MatrixFactory::Translate(-eye.x, -eye.y, -eye.z);
		return T * R;
	}

	Matrix4 Camera::createOrthographicProjectionMatrix(float left, float right, float top, float bottom, float near, float far) {
		Matrix4 ortho = Matrix4(1);
		ortho.elements[0 + 0 * 4] = 2 / (right - left);
		ortho.elements[1 + 1 * 4] = 2 / (top - bottom);
		ortho.elements[2 + 2 * 4] = 2 / (near - far);
		ortho.elements[0 + 3 * 4] = (left + right) / (left - right);
		ortho.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		ortho.elements[2 + 3 * 4] = (near + far) / (near - far);
		return ortho;
	}

	Matrix4 Camera::createPerspectiveProjectionMatrix(float fov, float aspect, float n, float f) {
		float angle = Math::angleToRad(fov / 2);
		float d = 1 / tan(angle);
		Matrix4 persp = Matrix4();
		persp.elements[0 + 0 * 4] = d / aspect;
		persp.elements[1 + 1 * 4] = d;
		persp.elements[2 + 2 * 4] = (n + f) / (n - f);
		persp.elements[3 + 2 * 4] = -1;
		persp.elements[2 + 3 * 4] = 2 * n * f / (n - f);
		return persp;
	}

	Matrix4 Camera::createPerspectiveProjectionMatrix(float fov, float with, float height, float n, float f) {
		float aspect = with / height;
		return createPerspectiveProjectionMatrix(fov, aspect, n, f);
	}

	Matrix4 Camera::rotateViewMatrix(Vector3 s, Vector3 u, Vector3 v) {
		Matrix4 rot = Matrix4(1);
		rot.elements[0 + 0 * 4] = s.x;
		rot.elements[0 + 1 * 4] = s.y;
		rot.elements[0 + 2 * 4] = s.z;
		rot.elements[1 + 0 * 4] = u.x;
		rot.elements[1 + 1 * 4] = u.y;
		rot.elements[1 + 2 * 4] = u.z;
		rot.elements[2 + 0 * 4] = -(v.x);
		rot.elements[2 + 1 * 4] = -(v.y);
		rot.elements[2 + 2 * 4] = -(v.z);
		return rot;
	}

	Matrix4 Camera::getViewMatrix() const {
		return viewMatrix;
	}

	Matrix4 Camera::getProjectionMatrix() const {
		if (ortho) {
			return orthographicMatrix;
		}
		else {
			return perspectiveMatrix;
		}
	}

	void Camera::toggleProjection() { 
		ortho = !ortho;
	}

	void Camera::createBufferObject() {
		glGenVertexArrays(1, &VaoId);
		glBindVertexArray(VaoId);
		glGenBuffers(1, &VboId);
		glBindBuffer(GL_UNIFORM_BUFFER, VboId); {
			glBufferData(GL_UNIFORM_BUFFER, Matrix4::size() * 2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, ubo_bp, VboId);
		}
	}

	void Camera::destroyBufferObject() const {
		glBindVertexArray(VaoId);
		glDeleteBuffers(1, &VboId);
		glDeleteVertexArrays(1, &VaoId);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Camera::draw() {
		glBindVertexArray(VaoId);
		glBindBuffer(GL_UNIFORM_BUFFER, VboId); {
			glBufferSubData(GL_UNIFORM_BUFFER, 0, Matrix4::size(), &getViewMatrix());
			glBufferSubData(GL_UNIFORM_BUFFER, Matrix4::size(), Matrix4::size(), &getProjectionMatrix());
		}
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindVertexArray(0);
	}
}