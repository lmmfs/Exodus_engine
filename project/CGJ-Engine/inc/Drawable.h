#pragma once

namespace engine {

	/**
	* Drawable interface
	*/
	class Drawable {

	public:

		/**
		* Performs the draw of this instance on the scene
		*/
		virtual void draw() = 0;
	};

};