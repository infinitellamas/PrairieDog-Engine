#pragma once

class Key {
public:
	Key() {}
	Key(char keyCode, bool isDown) {
		Key::_keyCode = keyCode;
		Key::_isDown = isDown;
	}

	char Key::getKeyCode() {
		return _keyCode;
	}

	bool Key::getKeyHeld() {
		return _isHeld;
	}

	bool Key::getKeyDown() {
		return _isDown;
	}

	bool Key::getKeyUp() {
		return _isUp;
	}

	void Key::setKeyDown(bool isDown) {
		_isDown = isDown;
	}

	void Key::setKeyHeld(bool isHeld) {
		_isHeld = isHeld;
	}

	void Key::setKeyUp(bool isUp) {
		_isUp = isUp;
	}
	// Next two are for use by the listener thread and key handler only, do not access from other funcs.
	void setAsyncIsKeyHeld(bool asyncIsHeld) {
		_asyncIsHeld = asyncIsHeld;
	}

	bool getAsyncIsKeyHeld() {
		return _asyncIsHeld;
	}
	//
private:
	char _keyCode;
	bool _isDown = false;
	bool _isHeld = false;
	bool _isUp = false;
	bool _asyncIsHeld = false;
};
