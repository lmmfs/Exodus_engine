#pragma once

#include <map>
#include <vector>

typedef void (*Function) ();

namespace engine {

	/**
	* Keybuffer class
	*
	* Manages the input keys that are pressed (only considers the keys that are configured by setCallback)
	*/
	class KeyBuffer {

	private:

		/**
		* Maps the key to it's callback
		*/
		static std::map<int, Function> functionMap;

		/**
		* Contains the state of each key (true if being pressed, false otherwise)
		*/
		static std::map<int, bool> activeMap;

	public:

		/**
		* Set the key to pressed or not
		*
		* @param int the key
		* @param bool the state for the key
		*/
		static void set(int, bool);

		/**
		* Get the state of the key
		*
		* @param int the key
		* @return the state for the key
		*/
		static bool isPressed(int);

		/**
		* Configures the key to a callback function
		*
		* @param int the key
		* @param Function the callback for the key
		*/
		static void setCallback(int, Function);

		/**
		* Iterates all keys and runs the callbacks for the ones that are pressed
		*
		*/
		static void runCallbacks();

	};

}