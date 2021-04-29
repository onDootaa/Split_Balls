#pragma once
#include "fmod.hpp"
#include <iostream>
#include <map>
#include <string>

class SoundEngine
{	
private:
	FMOD::System* system = nullptr;
	FMOD::Channel* channel=nullptr;
	std::map<std::string, FMOD::Sound*> pSounds;
	std::map<FMOD::Sound*, FMOD::Channel*> pChannel;

	FMOD_RESULT		result;
	unsigned int	version;
	void*			extradriverdata = nullptr;
	static int count;
	static SoundEngine* instance;

public:

	static SoundEngine* getInstance();

private:
	SoundEngine()
	{
		using namespace std;

		result = FMOD::System_Create(&system);
		if (result != FMOD_OK)
		{
			cout << "FMOD::System_Create() fail" << endl;
			exit(-1);
		}

		result = system->getVersion(&version);
		if (result != FMOD_OK)
		{
			cout << "getVersion() fail" << endl;
			exit(-1);
		}
		else printf("FMOD version %08x\n", version);

		result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (result != FMOD_OK)
		{
			cout << "system->init() fail" << endl;
			exit(-1);
		}
	}

public:
	~SoundEngine()
	{
		system->release();
	}

	void createSound(const std::string& filename, const std::string& soundName, const bool& isLoop)
	{
		pSounds[soundName] = nullptr;
		auto& soundPtr = pSounds[soundName];
		const int loopFlag = isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		
		result = system->createSound(filename.c_str(), loopFlag, 0, &soundPtr);
		if (result != FMOD_OK)
		{
			std::cout << "system->createSound() fail" << std::endl;
			exit(-1);
		}
	}

	void playSound(const std::string& _soundName, const bool& _simultaneus = false)
	{
		static int count = 0;
		if (pSounds.count(_soundName) <= 0)
		{
			std::cout << "isn't initialized." << std::endl;
			exit(-1);
		}

		const auto& soundPtr = pSounds[_soundName];
		auto channelPtr = pChannel[soundPtr];

		bool isPlaying = false;
		result = channelPtr->isPlaying(&isPlaying);
		if(_simultaneus==false) 
			if (isPlaying) { return;  }
		
		//std::cout << "sound = " << soundPtr << std::endl;
		//std::cout << "channel = " << channelPtr << std::endl;
		
		result = system->playSound(soundPtr, 0, false, &channelPtr);
		if (result != FMOD_OK)
		{
			std::cout << "system->playSound() fail" << std::endl;
			exit(-1);
		}
		
	}

	void stopSound(const std::string& _soundName)
	{
		if (pSounds.count(_soundName) <= 0) {
			std::cout << _soundName << " isn't initialized." << std::endl;
			exit(-1);
		}
		
		const auto& soundPtr = pSounds[_soundName];
		auto& channelPtr = pChannel[soundPtr];
		
		bool is_playing = false;
		result = channelPtr->isPlaying(&is_playing);

		if (is_playing == false)  return;  // don't stop playing if this is not playing

		result = channelPtr->stop();
		if (result != FMOD_OK) {
			std::cout << "system->playSound() fail" << std::endl;
			exit(-1);
		}
	}
};