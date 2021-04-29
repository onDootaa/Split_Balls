#pragma once
#include "actor.h"
#include "Game2D.h"
#include "bullets.h"


class Charactor :public Actor
{
private:
	float posX;	//x =0.0f, 
	float posY;	//y = should calculate btmStage's height
	float height = 0.2f;
	float width = 0.07f;
	int directionH = 0 ;// x:left(-1), front(0), right(1)
	int directionV = 0;
	int speed =2;
	int helth = 3;
	
	
public:
	std::vector<Bullets*> pBullets;
	//Charactor()
	//{}
	Charactor(const float& _posX,const float& _posY)
		:posX(_posX)
		,posY(_posY)
	{
		//posY += height / 2;
		//pBullets.reserve(100);
	}

	void draw();

	void moveLeft(const float& dt) override;
	void moveRight(const float& dt)override;
	void shooting(const float& dt)override;
	void jumping(const float& dt)override;
	float getPosX() { return posX; }
	float getPosY() { return posY; }
	void setPosX(const float& _x) { posX = _x; }
	void setPosY(const float& _y) { posY = _y; }
	int getDirectionH() { return directionH; }
	float gethalfWidth() { return width/2; }
	//void bull_cntpp() { bull_cnt++; }
	//int getBull_cnt() { return bull_cnt; }
};