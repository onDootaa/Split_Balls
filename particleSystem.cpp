#include "ParticleSystem.h"
#include "SoundEngine.h"
//jm::ParticleSystem::ParticleSystem()
//{
//	//reset();
//}

auto ParticleSystem::getRandomUnitVector()
{
	const float theta = rn.getFloat(0.0f, 3.141592f * 2.0f); // 0.0 ~ 2pi

	return vec2{ cos(theta), -sin(theta) };
}

auto ParticleSystem::getRandomColor()
{
	return RGB{ rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f) };
}

void ParticleSystem::explode(const vec2& _pos )
{
	SoundEngine::getInstance()->playSound("explode", true);
	//particles.clear();
	//SoundEngine::getInstance()->playSound("explode_fizz", true);
	// initialize particles
	//std::cout << "BANG" << std::endl;
	for (int i = 0; i < 100; ++i)
	{
		Particles new_particle;
		new_particle.pos = _pos;
		new_particle.vel = getRandomUnitVector() * rn.getFloat(-0.01f, 3.0f);
		new_particle.rot = rn.getFloat(0.01f, 2.0f * 3.141592f) * 360.0f;
		new_particle.angular_velocity = rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;
		new_particle.color = getRandomColor();
		new_particle.age = 0.0f;
		new_particle.life = rn.getFloat(0.1f, 1.0f);

		particles.push_back(new_particle);
		//std::cout << "\tpos = " <<new_particle.pos<< std::endl;
	}
}

void ParticleSystem::update(const float& dt)
{
	for (auto& pt : particles)
	{
		pt.update(dt);

		// remove particles when they are 1. too old, 2. out of screen.
	}
}

void ParticleSystem::draw()
{
	beginTransformation();

	for (const auto& pt : particles)
	{
		if (pt.life < pt.age) continue;	// dead

		const float color_alpha = (1.0f - pt.age / pt.life) * rn.getFloat(0.0f, 1.0f);

		const RGB blended_color = {
			pt.color.r * color_alpha + 1.0f * (1.0f - color_alpha),
			pt.color.g * color_alpha + 1.0f * (1.0f - color_alpha),
			pt.color.b * color_alpha + 1.0f * (1.0f - color_alpha)
		};

		//drawPoint(blended_color, pt.pos, 3.0f);
		beginTransformation();
		translate(pt.pos);
		rotate(pt.rot);
		drawFilledStar(blended_color, 0.03f, 0.01f);
		endTransformation();
	}

	endTransformation();
}
