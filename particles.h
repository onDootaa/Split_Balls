#pragma once
#include "Game2D.h"
#include <vector>
#include <memory>
#include "RandomNumberGenerator.h"



static const auto gravity = vec2(0.0f, -9.8f);
class Particles
{
public:
	vec2 pos;
	vec2 vel;
	float rot;
	float angular_velocity;
	RGB  color;
	float age;
	float life;
public:
	Particles()
	{}
	
	Particles(vec2 _pos, vec2 _vel, float _rot,
		float _angular_velocity, RGB _color, float _age, float _life);
	void update(const float& dt);
};
