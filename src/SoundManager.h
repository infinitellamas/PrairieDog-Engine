#pragma once
#include "Sound.h"
#include "bass.h"
#include <vector>
#include <string>
#include <iostream>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	// Adds a sound to the sound pool. You should only add one sound per fileName, and just play that sound many times.
	void addSound(std::string fileName);
	// Removes all sounds defined by the fileName.
	void removeSound(std::string fileName);
	// Returns the first sound defined by the filename, if a sound does not exist at that filename, it returns a blank Sound object.
	Sound getSound(std::string fileName);
	// Plays a sound defined by the fileName once.
	HCHANNEL playSound(std::string fileName);
	// Loops a sound until the user calls stopSound.
	void loopSound(std::string fileName); // TODO
	// Stops a sound, useful for stopping loops.
	void stopSound(std::string fileName);
private:
	std::vector<Sound> _sounds;
	BASS_INFO info;
};

