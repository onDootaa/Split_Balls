#pragma once
#include "Game2D.h"

class Projectiles
{
private:
	const float elasticity = 1.0f;
	vec2 position;
	vec2 velocity;
	float radius;
	RGB color;
	float mass;
public:
	Projectiles(vec2 _pos, vec2 _vel, float _radius, RGB _color)
		:position(_pos),  radius(_radius), color(_color),velocity(_vel)
	{
		mass = std::pow(radius, 2.0f) * 5.0f;
	}

	void draw()
	{
		beginTransformation();
		{
			translate(position);
			drawFilledCircle(color, radius);
		}
		endTransformation();
	}

	virtual void update(const float& dt) {};
	
	//get function
	vec2 getPos() { return position; }
	vec2 getVel() { return velocity; }
	RGB getColor()	{return color;	}
	float getR()	{return radius;	}
	float getMass() { return mass; }
	float getK() { return elasticity; }

	//set Position
	void setPos(const vec2& _pos){position = _pos;}
	void setPos(const float& _posX, const float& _posY)	{position = vec2(_posX, _posY);}
	void setPosX(const float& _val) { position.x = _val; }
	void setPosY(const float& _val) { position.y = _val; }

	//set Velocity
	void setVel(const vec2& _vel){velocity = _vel;}
	void setVel(const float& _velX, const float& _velY)	{velocity = vec2(_velX, _velY);}
	void setVelX(const float& _val) { velocity.x = _val; }
	void setVelY(const float& _val) { velocity.y = _val; }

	void setR(const float& _rad){radius = _rad;	}
	void setColor(const RGB& _color){color = _color;}
	void setMass(const float& _m) { mass = _m; }
};