#pragma once

#include "Drawable.h"
#include "BufferObject.h"
#include "Utils.h"
#include "maths/Matrix.h"
#include "maths/Quaternion.h"
#include <GL/glew.h>

namespace engine {

	/**
	* Camera class 
	*/
	class Camera : public Drawable, BufferObject {
	private:

		// The shader variables
		GLuint VaoId, VboId, ubo_bp;

		// View properties
		Vector3 eye = Vector3(1.0, 0.0, 20.0);
		Vector3 center = Vector3(0, 0, 0);
		Vector3 up = Vector3(0, 1, 0);
		Vector3 worldUp = Vector3(0, 1, 0);
		Vector3 right = Vector3(1, 0, 0);
		Matrix4 rx;
		Matrix4 ry;
		Quaternion orientation = Quaternion();

		// Control properties
		float first_direction = true;
		float previous_x = 0.0f, previous_y = 0.0f;
		float yaw = -90.0f, pitch = 0.0f;
		float cameraSpeed = 20.0f;
		float mouseSensitivity = 0.1f;
		float aspect = 640 / 480;
		float deltaTime = 0.02f;

		// Projection properties
		float distance = 4.0f;
		float l = 0.0f;
		float r = 0.0f;
		float t = 0.0f;
		float b = 0.0f;
		float n = 0.0f;
		float f = 0.0f;
		float fov = 45.0f;

		// Matrices to pass to shader
		Matrix4 viewMatrix;
		Matrix4 orthographicMatrix;
		Matrix4 perspectiveMatrix;

		bool ortho = false;
		bool gLock = false;

		//////////////////
		// Constructors //
		//////////////////

	public:

		void setViewMatrix(Matrix4 view) { viewMatrix = view; }

		/**
		* Constructs a Camera, giving the UBO buffer pointer for the matrices
		*
		* @param ubo_bp the UBO buffer pointer
		*/
		Camera(const GLuint);
		
		/**
		* Constructs a Camera, giving the UBO buffer pointer for the matrices
		* and properties
		*
		* @param ubo_bp the UBO buffer pointer
		* @param l the box left offset
		* @param r the box right offset
		* @param t the box top offset
		* @param b the box bottom offset
		* @param n the near clipping property
		* @param f the far clipping property
		* @param distance the distance to the target
		* @param winx the window width
		* @param winy the window height
		*/
		Camera(const GLuint, float l, float r, float t, float b, float n, float f, float distance, int winx, int winy);

		/**
		* Destroys this Camera
		*/
		~Camera();

		//////////////
		// Matrices //
		//////////////

				/**
		* Create the Orthographic Projection Matrix
		*
		* @param l the box left offset
		* @param r the box right offset
		* @param t the box top offset
		* @param b the box bottom offset
		* @param n the near clipping property
		* @param f the far clipping property
		* @return the Orthographic Projection Matrix
		*/
		Matrix4 createOrthographicProjectionMatrix(float l, float r, float t, float b, float n, float f);

		/**
		* Creates the View Matrix based on the position, target and up vectors
		*
		* @param eye the camera's position
		* @param center the target's position
		* @param up the Up vector
		* @return the View Matrix
		*/
		Matrix4 createViewMatrix(Vector3 eye, Vector3 center, Vector3 up);

	private:

		/**
		* Creates the View Matrix based on the X and Y rotations
		*
		* @param rx the rotation in X
		* @param ry the rotation in Y
		* @return the View Matrix
		*/
		Matrix4 createViewMatrix2(Matrix4 rx, Matrix4 ry);

		/**
		* Create the Perspective Projection Matrix
		*
		* @param fov the field-of-view property
		* @param aspect the aspect ratio
		* @param n the near clipping property
		* @param f the far clipping property
		* @return the Perspective Projection Matrix
		*/
		Matrix4 createPerspectiveProjectionMatrix(float fov, float aspect, float n, float f);

		/**
		* Create the Perspective Projection Matrix
		*
		* @param fov the field-of-view property
		* @param width the clipping width
		* @param height the clipping height
		* @param n the near clipping property
		* @param f the far clipping property
		* @return the Perspective Projection Matrix
		*/
		Matrix4 createPerspectiveProjectionMatrix(float fov, float width, float height, float n, float f);

		/**
		* Create Rotation part of View Matrix
		*
		* @param s the side or right vector
		* @param u the up vector
		* @param v the view or forward vector
		* @return the Rotation part of the View Matrix
		*/
		Matrix4 rotateViewMatrix(Vector3 s, Vector3 u, Vector3 v);

	public:

		Vector3 getEye() { return eye; }

		/**
		* Gets the View Matrix
		*
		* @return the View Matrix
		*/
		Matrix4 getViewMatrix() const;
			
		/**
		* Gets the Projection Matrix, either Orthographic or Perspective
		*
		* @return the Projection Matrix
		*/
		Matrix4 getProjectionMatrix() const;

		/**
		* Toggles the Projection between Orthographic and Perspective
		*/
		void toggleProjection();

		/**
		* Recalculates the view and projection matrices
		*/
		void recalculateMatrices();

		/**
		* Recalculates projection based on type
		* (to be removed)
		*/
		void updateProjection();

		////////////////
		// Properties //
		////////////////

	public:

		/**
		* Sets the Aspect Ratio
		*
		* @param asp the Aspect Ratio to set
		*/
		void setAspect(float asp) { aspect = asp; };

		/**
		* Set the Delta
		*
		* @param delta the Delta to set
		*/
		void setDelta(float delta);

		/**
		* Sets the Distance
		*
		* @param newDistance the Distance to set
		*/
		void setDistance(float newDistance) { distance = newDistance; }

		/**
		* Toggles Gimbal lock on or off
		*/
		void toggleGimbalLock();

		/////////////////////
		// Control Updates //
		/////////////////////

	public:

		/**
		* Moves the Camera one unit in the mov direction
		*
		* @param mov the character of direction (u, d, l or r)
		*/
		void updateEye(const char* mov);

		/**
		* Updates the View Matrix based on a rotation orientation
		*
		* @param xpos the X position of the cursor
		* @param ypos the Y position of the cursor
		*/
		void updateViewMatrix2(float xpos, float ypos);

		/**
		* Updates the Field of View based on cursor position
		*
		* @param xoffset the difference in the X position
		* @param yoffset the difference in the Y position
		*/
		void updateFoV(double xoffset, double yoffset);

		/**
		* Updates the orientation based on cursor position
		*
		* @param xpos the X position of the cursor
		* @param ypos the Y position of the cursor
		*/
		void updateDirection(float xpos, float ypos);

		/**
		* Resets the camera position and orientation to the original state
		*/
		void resetCenter();

		////////////////////////////////////////////////////////
		// BufferObject - @see BufferObject.h for definitions //
		////////////////////////////////////////////////////////

	private:

		void createBufferObject() override;

		void destroyBufferObject() const override;

		////////////////////////////////////////////////
		// Drawable - @see Drawable.h for definitions //
		////////////////////////////////////////////////

	public:

		void draw() override;

	};
}
