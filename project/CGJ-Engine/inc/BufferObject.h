#pragma once

namespace engine {

	/**
	* VAO and VBOs buffer object interface
	*/
	class BufferObject {

	private:

		/**
		* Creates the VAO and VBOs for this instance
		*/
		virtual void createBufferObject() = 0;

		/**
		* Destroys the VAO and VBOs of this instance
		*/
		virtual void destroyBufferObject() const = 0;

	};

}