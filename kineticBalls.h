#pragma once
#include "DrawFunctions.h"
#include "Colors.h"
#include <math.h>
#include "projectile.h"


class kineticBalls:public Projectiles
{
private:
	//const float epsilon = 0.03f; 
	int step;
	int durability; // given larger number on higher stage
	float deminution = 0.9f; // when ball split, reduce the height of splited balls
	float deltaX = 0.1f; // when ball split, displace the splited balls X positions

public:
	
	kineticBalls(vec2 _pos, vec2 _vel, float _radius, RGB _color, int _step, int _durability)
		:Projectiles(_pos, _vel, _radius, _color)
		, step(_step)
		, durability(_durability)
	{}
	~kineticBalls()
	{}
	void init();

	void update(const float& dt) override;
	//void thresholdFilter(vec2& _val) // any value smaller than epsilon set zero
	//{
	//	_val.x = (abs(_val.x) <= epsilon) ? 0 : _val.x;
	//	_val.y = (abs(_val.y) <= epsilon) ? 0 : _val.y;
	//}
	void upStep()	{ step++; }
	int getHp()		{ return durability;}
	int getStep()	{ return step; }
	void setHp(const int& _val) { durability = _val; }
	float getDeminution() { return deminution; }
	float getDeltaX() { return deltaX; }
};