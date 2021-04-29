#include "bullets.h"

Bullets::Bullets(const vec2& _pos, const RGB& _color, const float& _radius, vec2 _vel, const int& _weapon, const int& _impact, const float& _gunHeight)
	:Projectiles(_pos, _vel, _radius, _color), impact(_impact), weapon(_weapon)
{
	setPosY(getPos().y + _gunHeight); //modifying gun's end point 
	setVel(getVel() * static_cast<float>(_weapon));
	//setMass(0.0f);
	SoundEngine::getInstance()->playSound("cannon",true);
}

Bullets::~Bullets()
{
	SoundEngine::getInstance()->stopSound("cannon");
	//std::cout << "eraser works." << std::endl;
}

//static int bullets_cnt = 0;
void Bullets::draw()
{
	beginTransformation();
	{
		translate(getPos());
		drawFilledCircle(getColor(), getR());
	}
	endTransformation();
}

void Bullets::update(const float& dt)
{
	setPos(getPos() + getVel() * dt);
	if (isCollid)
	{
		if (life > 0)
		{
			life -= dt;
			const float color_alpha = life;
			const RGB blended_color = {
				getColor().r * color_alpha + 1.0f * (1.0f - color_alpha),
				getColor().g * color_alpha + 1.0f * (1.0f - color_alpha),
				getColor().b * color_alpha + 1.0f * (1.0f - color_alpha) };
			setColor(blended_color);
		}
		else
			life = 0;
	}
	
}

bool Bullets::isOut(const float& _bottom, const float& _top, const float& _left, const float& _right)
{
	//erase bullet
	if ((getPos().x > _right + getR()) || (getPos().x < _left - getR())
		|| (getPos().y > _top + getR()) || (getPos().y < _bottom - getR()))
	{
		return true; 
	}
	return false;
}
