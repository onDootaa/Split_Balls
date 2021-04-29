#include "charactor.h"

void Charactor::draw()
{
	beginTransformation();
	translate(posX, posY + height * 0.5f);
	drawFilledBox(Colors::hotpink, width, height);
	endTransformation();
}

void Charactor::moveLeft(const float& dt)
{
	directionH = -1;
	posX += directionH * speed * dt;
}

void Charactor::moveRight(const float& dt)
{
	directionH = +1;
	posX += directionH * speed * dt;
}

void Charactor::shooting(const float& dt)
{// later make pBullets in the StageWall class  << bull_cnt++ 
	pBullets.push_back(new Bullets({ posX, posY }, Colors::red, 0.02f, vec2(0.0f, 5.0f), 1, 1, height));
}

void Charactor::jumping(const float& dt)
{
	//should make jumping action

}
