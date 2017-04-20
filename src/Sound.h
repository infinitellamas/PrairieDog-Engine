#pragma once
#include "bass.h"
#include <string>

class Sound {
public:
	Sound() {}

	Sound(std::string filename) {
		_filename = filename;
		_sample = BASS_SampleLoad(FALSE, filename.c_str(), 0, 0, 20, BASS_SAMPLE_OVER_POS);
	}

	HSAMPLE getSample() {
		return _sample;
	}

	std::string getFileName() {
		return _filename;
	}

	HCHANNEL getChannel() {
		return BASS_SampleGetChannel(_sample, FALSE);
	}

private:
	std::string _filename;
	HCHANNEL _ch;
	HSAMPLE _sample;
};