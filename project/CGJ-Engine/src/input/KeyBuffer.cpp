#include "input/KeyBuffer.h"
namespace engine {

	std::map<int, Function> KeyBuffer::functionMap;
	std::map<int, bool> KeyBuffer::activeMap;

	void KeyBuffer::set(int key, bool active) {
		activeMap[key] = active;
	}

	bool KeyBuffer::isPressed(int key) {
		return activeMap[key];
	}

	void KeyBuffer::setCallback(int key, Function callback) {
		functionMap.insert(std::pair<int, Function>(key, callback));
	}

	void KeyBuffer::runCallbacks() {
		for (std::pair<int, bool> key : activeMap) {
			std::map<int, Function>::iterator it = functionMap.find(key.first);
			if (key.second && it != functionMap.end()) {
				it->second();
			}
		}
	}
}