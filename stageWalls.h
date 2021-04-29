#pragma once
#include <vector>
#include "DrawFunctions.h"
#include "Colors.h"
#include "kineticBalls.h"
#include "charactor.h"
#include "particleSystem.h"
#include "SoundEngine.h"

class StageWalls//:public Execute
{
private:
	//const float coef_fric = 1.0f; //firction
	//const float coef_rest = 1.0f; //restitution
	const float ratio = 4.0f / 3.0f;
	float halfHeight = 1.0f;
	float bL_x = -ratio * halfHeight;
	float bR_x = ratio * halfHeight;
	float bB_y = -halfHeight;
	float bT_y = halfHeight;
	float stageBoxWidth = 2 * ratio;
	float stageBoxHeight = 0.25f;
	float thick = 0.3f; // line width 
	float ballsRaius[5] = { 0.16f,0.12f,0.1f,0.08f,0.06f };
	int ballsHp[5] = { 50,30,22,16,7 };
	int stageLevel = 5;

	Charactor myCharactor{ 0.0f, stageBoxHeight - 1 };
	std::vector<kineticBalls*> pBalls;
	RandomNumberGenerator rn;
	ParticleSystem ps;

public:
	friend class Execute;
	//friend class Charactor;

	StageWalls()
	{
		auto& soundEngine = *SoundEngine::getInstance();
		soundEngine.createSound("./sound/hit.wav", "cannon", false);
		soundEngine.createSound("./sound/explode_fizz.wav", "explode", false);
		soundEngine.createSound("./sound/foley_glass_break.wav", "split", false);

		RGB ballColor = RGB(rn.getInt(0, 255), rn.getInt(0, 255), rn.getInt(0, 255));
		pBalls.push_back(new kineticBalls(vec2(-0.7f, 0.7f), vec2(1.5f, 0.0f), 
			ballsRaius[0], ballColor,0,ballsHp[0]));
	}

	~StageWalls()
	{}
	void draw();
	void reset();
	void newBall();
	void splitBalls(kineticBalls& _ball);
	void update(const float& dt);
	void isCollid(kineticBalls& _b0, Bullets& _b1);
	//bool isImpact(Bullets& _bullet, kineticBalls& _ball);
	float getbL_x()const { return bL_x; }
	float getbR_x()const { return bR_x; }
	float getbB_y()const { return bB_y; }
	float getStageBoxHeight()const { return stageBoxHeight; }
	float getHalfHeight()const { return halfHeight; }
	void setbL_x(const float& _val) { bL_x = _val; }
	void setbR_x(const float& _val) { bR_x = _val; }
	void setbB_y(const float& _val) { bB_y = _val; }
	void setHalfHeight(const float& _val) { halfHeight = _val; }
	//judge bumping against boarder
	void isBump(kineticBalls& _ball);
};

