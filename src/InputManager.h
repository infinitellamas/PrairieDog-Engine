#pragma once
#include <vector>
#include <future>
#include <thread>
#include "Key.h"
#include "Windows.h"


class InputManager
{
public:
	InputManager();
	~InputManager();
	// Tells the inputManager to listen for a key.
	void listenForKey(char keyCode);
	//Returns a key so you can check if its pressed or not.
	Key getKey(char keyCode);

	void updateKeys();
	

private:
	void _startListening();
	void _stopListening();
	int _updateAsync();
	std::vector<Key> _keys;
	bool _keepListening = true;
	std::future<int> keyListener;

};

