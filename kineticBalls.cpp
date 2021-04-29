#include "kineticBalls.h"

void kineticBalls::init()
{// starting point coordinate & velocity
	setPos(vec2(-0.7f, 0.5f));
	setVel(vec2(5.0f, 3.0f));
}

void kineticBalls::update(const float& dt)
{
	setVelY(getVel().y + Gravity * dt);// when velocity is lower than epsilon speed = 0;
	setPos(getPos() + getVel() * dt);

}
