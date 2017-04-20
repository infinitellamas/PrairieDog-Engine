#include "InputManager.h"



InputManager::InputManager()
{
	_startListening();
}

void InputManager::listenForKey(char keyCode) {
	_keys.push_back(Key(keyCode, false));
}

Key InputManager::getKey(char keyCode) {
	for (unsigned int i = 0; i < _keys.size(); i++) {
		if (_keys.at(i).getKeyCode() == keyCode) {
			return _keys.at(i);
		}
	}
	return Key();
}

int InputManager::_updateAsync() {
	INPUT_RECORD inputRecord;
	HANDLE consoleHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD inputNum = 0;
	DWORD readNum = 0;

	GetNumberOfConsoleInputEvents(consoleHandle, &inputNum);
	while (_keepListening) {
		ReadConsoleInput(consoleHandle, &inputRecord, 1, &readNum);
		for (unsigned int k = 0; k < _keys.size(); k++) {
			if (_keys.at(k).getKeyCode() == inputRecord.Event.KeyEvent.uChar.AsciiChar) {
				_keys.at(k).setAsyncIsKeyHeld(inputRecord.Event.KeyEvent.bKeyDown);
			}
		}
	}
	return 0;
}

void InputManager::updateKeys() {
	for (unsigned int i = 0; i < _keys.size(); i++) {
		if (!_keys.at(i).getAsyncIsKeyHeld() && _keys.at(i).getKeyHeld()) { // If key not held now, but held last frame.
			_keys.at(i).setKeyDown(false);
			_keys.at(i).setKeyHeld(false);
			_keys.at(i).setKeyUp(true);
		}
		else if (_keys.at(i).getAsyncIsKeyHeld() && !_keys.at(i).getKeyHeld()) { //If key held now, but not last frame
			_keys.at(i).setKeyDown(true);
			_keys.at(i).setKeyHeld(true);
			_keys.at(i).setKeyUp(false);
		}
		else if (_keys.at(i).getKeyHeld() && _keys.at(i).getKeyDown()) { // if key down last frame and down this frame
			_keys.at(i).setKeyDown(false);
			_keys.at(i).setKeyHeld(true);
			_keys.at(i).setKeyUp(false);
		}
		else if (!_keys.at(i).getAsyncIsKeyHeld() && !_keys.at(i).getKeyHeld()) { // If up this frame, and up last frame.
			_keys.at(i).setKeyDown(false);
			_keys.at(i).setKeyHeld(false);
			_keys.at(i).setKeyUp(false);
		}
	}
}

void InputManager::_startListening() {
	_keepListening = true;
	keyListener = std::async(&InputManager::_updateAsync, this); //Idk if this will work.
}

void InputManager::_stopListening() {
	_keepListening = false;
}

InputManager::~InputManager()
{
	_stopListening();
}

