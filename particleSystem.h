#pragma once
#include "RandomNumberGenerator.h"
#include "Particles.h"



class ParticleSystem
{
private:
	std::vector<Particles> particles;
	RandomNumberGenerator rn;

public:
	ParticleSystem()
	{}

	auto getRandomUnitVector();

	auto getRandomColor();

	void explode(const vec2& _pos);

	void update(const float& dt);

	void draw();
};

