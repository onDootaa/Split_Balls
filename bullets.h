#pragma once
#include "DrawFunctions.h"
#include "Colors.h"
#include "projectile.h"
#include "SoundEngine.h"
//#include "SoundEngine_Singleton.h"
static int bullets_cnt;
class Bullets:public Projectiles
{
private:
	int impact = 1;
	float life = 1.0f;
	bool isCollid = false;
	int weapon = 1;
	int bulletsTotal = 0;

public:

	Bullets(const vec2& _pos,  const RGB& _color, const float& _radius, 
		vec2 _vel, const int& _weapon, const int& _impact, const float& _gunHeight);
	~Bullets();
	void draw();
	void update(const float& dt) override;
	bool isOut(const float& _bottom, const float& _top, const float& _left, const float& _right);
	int getImpact()const	{ return impact; }
	float getLife()const { return life; }
	void setLife(const float& _dt) { life -= _dt; }
	bool getCollid()const { return isCollid; }
	void setCollideTrue() { isCollid = true; }
	void setImpact(const int& _p) { impact = _p; }
	void setBullet_cnt(const int& _cnt) { bullets_cnt = _cnt; }
	int getBullets_cnt()const { return bullets_cnt; }
};