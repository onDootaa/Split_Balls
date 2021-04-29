#include "Particles.h"

Particles::Particles(vec2 _pos, vec2 _vel, float _rot, float _angular_velocity, RGB _color, float _age, float _life)
	:pos(_pos), vel(_vel), rot(_rot), angular_velocity(_angular_velocity), color(_color), age(_age), life(_life)
{}

void Particles::update(const float& dt)
{
	const auto acc = gravity; //assumes GA only.

	vel += acc * dt;
	pos += vel * dt;

	rot += angular_velocity * dt;

	// update age.
	age += dt;

	// update color (blend with background color)
}
