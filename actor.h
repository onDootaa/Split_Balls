#pragma once
//#include "bullets.h"

class Actor
{
public:

	//moveLeft
	virtual void moveLeft(const float& dt) = 0;
	//moveRight
	virtual void moveRight(const float& dt) = 0;
	//shooting
	virtual void shooting(const float& dt) = 0;
	//jumping
	virtual void jumping(const float& dt) = 0;
};