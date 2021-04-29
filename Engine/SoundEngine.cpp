#include "SoundEngine.h"

SoundEngine* SoundEngine::instance = nullptr;

SoundEngine* SoundEngine::getInstance()
{
	if (instance == nullptr)
		instance = new SoundEngine;
	return instance;
}
