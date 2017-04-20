#include "SoundManager.h"

SoundManager::SoundManager()
{
		std::cout << "SoundManager init";
		if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
			std::cout << " fail." << std::endl;
			std::cout << "An error has occurred initializing the BASS Audio Library, sound will be disabled." << std::endl;
			std::cout << "Sorry about that!" << std::endl;
		}
		else {
			BASS_GetInfo(&info);
			if (!info.freq) info.freq = 44100;
			std::cout << " success." << std::endl;
		}
}

void SoundManager::addSound(std::string fileName) {
	std::cout << "Loading sound " << fileName;
	Sound sound = Sound(fileName);
	if (!BASS_ErrorGetCode()) {
		std::cout << " success." << std::endl;
		SoundManager::_sounds.push_back(sound);
	}
	else {
		std::cout << " failed with errorcode " << BASS_ErrorGetCode() << std::endl;
	}
}
void SoundManager::removeSound(std::string fileName) {
	for (unsigned int i = 0; i < _sounds.size(); i++) {
		if (_sounds.at(i).getFileName() == fileName) {
			_sounds.erase(_sounds.begin() + i);
		}
	}
}

Sound SoundManager::getSound(std::string fileName) {
	for (unsigned int i = 0; i < _sounds.size(); i++) {
		if (_sounds.at(i).getFileName() == fileName) {
			return _sounds.at(i);
		}
	}
	return Sound();
}

void SoundManager::playSound(std::string fileName) {
	for (unsigned int i = 0; i < _sounds.size(); i++) {
		if (_sounds.at(i).getFileName() == fileName) {
			HCHANNEL ch = _sounds.at(i).getChannel();
			BASS_ChannelSetAttribute(ch, BASS_ATTRIB_VOL, 1);
			BASS_ChannelSetAttribute(ch, BASS_ATTRIB_PAN, 0);
			BASS_ChannelPlay(ch, FALSE);
		}
	}
}

void SoundManager::loopSound(std::string fileName) {
	// TODO
}

void SoundManager::stopSound(std::string fileName) {
	for (unsigned int i = 0; i < _sounds.size(); i++) {
		if (_sounds.at(i).getFileName() == fileName) {
			HCHANNEL ch = _sounds.at(i).getChannel();
			BASS_ChannelStop(ch);
		}
	}
}

SoundManager::~SoundManager()
{
}
