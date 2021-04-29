#include "stageWalls.h"


void StageWalls::draw()//draw screen border & bottom stage
{
	setLineWidth(thick);
	//left wall
	drawLine(Colors::red, vec2(bL_x, bT_y), Colors::blue, vec2(bL_x, bB_y));
	//bottom wall
	drawLine(Colors::blue, vec2(bL_x, bB_y), Colors::green, vec2(bR_x, bB_y));
	//Right wall
	drawLine(Colors::green, vec2(bR_x, bB_y), Colors::blue, vec2(bR_x, bT_y));
	// RGB(rn.getInt(0, 255), rn.getInt(0, 255), rn.getInt(0, 255)), i));
	beginTransformation();
	translate(0.0f, -0.875f);
	drawFilledBox(Colors::green, stageBoxWidth, stageBoxHeight);
	endTransformation();
}

void StageWalls::update(const float& dt)
{
	//character
	myCharactor.draw();
	if (myCharactor.getPosX() < (bL_x+myCharactor.gethalfWidth())
		&& myCharactor.getDirectionH() == -1)
	{
		myCharactor.setPosX(bL_x + myCharactor.gethalfWidth());
	}
	if (myCharactor.getPosX() > (bR_x - myCharactor.gethalfWidth())
		&& myCharactor.getDirectionH() == +1)
	{
		myCharactor.setPosX(bR_x - myCharactor.gethalfWidth());
	}

	//bullets 
	for (int i = static_cast<int>(myCharactor.pBullets.size() - 1); i >= 0; i--)
	{
		myCharactor.pBullets[i]->draw();
		myCharactor.pBullets[i]->update(dt);
		if (myCharactor.pBullets[i]->isOut(bB_y, bT_y, bL_x, bR_x))
		{
			myCharactor.pBullets[i]->~Bullets();
			myCharactor.pBullets.erase(myCharactor.pBullets.begin() + i);
			//[(myCharactor.pBullets.begin() + i)]
		}
	}

	//balls 
	for (int i = 0; i < pBalls.size(); i++)
	{
		pBalls[i]->update(dt);
		isBump(*pBalls[i]);// , coef_rest, coef_fric);
		//*******************************************
		//*** handling bound of ball's collisions ***
		//*******************************************
		//if (pBalls.size() >= 2)
		//{
		//	for (int j = i + 1; j < pBalls.size(); j++)
		//	{
		//		isCollid(*pBalls[i], *pBalls[j]);
		//	}
		//}
		pBalls[i]->draw();
	}
	//function distinguishing hitted balls by bullets
	for (int i = static_cast<int>(pBalls.size() - 1); i >= 0; i--)
	{
		for (int j = static_cast<int>(myCharactor.pBullets.size() - 1); j >= 0; j--)
		{
			if (myCharactor.pBullets[j]->getCollid()) continue;
			isCollid(*pBalls[i], *myCharactor.pBullets[j]);
			//if (isImpact(*myCharactor.pBullets[j], *pBalls[i])) 
			//{
			//	//myCharactor.pBullets.erase(myCharactor.pBullets.begin() + j);
			//	//std::cout << "ball_" << i << "'s Hp = " << pBalls[i]->getHp() << std::endl;
			//}
		}
		if (pBalls[i]->getHp() <= 0)
		{
			splitBalls((*pBalls[i]));
			pBalls.erase(pBalls.begin() + i);

		}
	}
	ps.update(dt);
	ps.draw();
}

void StageWalls::reset()
{
	pBalls.clear();

}
void StageWalls::newBall()
{
	RGB ballColor = RGB(rn.getInt(0, 255), rn.getInt(0, 255), rn.getInt(0, 255));
	pBalls.push_back(new kineticBalls(vec2(-0.7f, 0.7f), vec2(1.5f, 0.0f),
		ballsRaius[0], ballColor, 0, ballsHp[0]));
}
// make Balls movement does not affected by bullets impact
void StageWalls::isCollid(kineticBalls& _b0, Bullets& _b1)
{
	const float distance = (_b0.getPos() - _b1.getPos()).getMagnitude();
	float twoRaius = _b0.getR() + _b1.getR();
	if (distance <= twoRaius)
	{
		float delta = distance - twoRaius; //delta is always smaller than 0
		// compute impulse
		const auto vel_rel = _b0.getVel() - _b1.getVel();
		const auto normal = -(_b1.getPos() - _b0.getPos()) / distance;
		//// modifing overlabed two balls' position 
		//_b0.setPos(_b0.getPos().x + delta * -normal.x * _b0.getR() / twoRaius,true);  //true is x
		//_b0.setPos(_b0.getPos().y + delta * -normal.y * _b0.getR() / twoRaius,false); //false is y
		_b1.setPosX(_b1.getPos().x + delta * normal.x * _b1.getR() / twoRaius);
		_b1.setPosY(_b1.getPos().y + delta * normal.y * _b1.getR() / twoRaius);

		if (vel_rel.getDotProduct(normal) < 0.0f) // approaching
		{
			const auto impulse = normal * -(1.0f + (_b0.getK() + _b1.getK()) / 2) * vel_rel.getDotProduct(normal) /
				((1.0f / _b0.getMass()) + (1.0f / _b1.getMass()));
			// update velocities of two bodies
			//_b0.setVel(_b0.getVel().x + impulse.x / _b0.getMass(), true);
			//_b0.setVel(_b0.getVel().y + impulse.y / _b0.getMass(), false);
			_b1.setVelX(_b1.getVel().x - impulse.x / _b1.getMass());
			_b1.setVelY(_b1.getVel().y - impulse.y / _b1.getMass());
		}
		_b0.setHp(_b0.getHp() - _b1.getImpact());
		_b1.setCollideTrue();
	}
}

//judge bumping against boarder

void StageWalls::isBump(kineticBalls& _ball)
{
	//right																		
	if (_ball.getPos().x >= (bR_x - _ball.getR()))
	{
		_ball.setPosX(bR_x - _ball.getR());
		if (_ball.getVel().x >= 0)
			_ball.setVelX(_ball.getVel().x * -1);
	}
	//left
	if (_ball.getPos().x <= (bL_x + _ball.getR()))
	{
		_ball.setPosX(bL_x + _ball.getR());
		if (_ball.getVel().x <= 0)
			_ball.setVelX(_ball.getVel().x * -1);
	}
	//bottom
	if (_ball.getPos().y <= bB_y + _ball.getR())
	{
		_ball.setPosY(bB_y + _ball.getR());
		if (_ball.getPos().y <= 0)
			_ball.setVelY(_ball.getVel().y * -1);// -_coef_rest;
	}
}

void StageWalls::splitBalls(kineticBalls& _ball) // each time creat a ball, radius be smaller step -1 by array 
{
	SoundEngine::getInstance()->playSound("split",true);
	vec2 ballVel = vec2(abs(_ball.getVel().x), abs(_ball.getVel().y));
	RGB ballColor = RGB(rn.getInt(0, 255), rn.getInt(0, 255), rn.getInt(0, 255));
	_ball.upStep();
	if (_ball.getStep() < stageLevel) 
	{
		pBalls.push_back(new kineticBalls(vec2(_ball.getPos().x + _ball.getDeltaX(), _ball.getPos().y * _ball.getDeminution()), vec2(ballVel.x, ballVel.y),
			ballsRaius[_ball.getStep()], ballColor, _ball.getStep(), ballsHp[_ball.getStep()]));
		ballColor = RGB(rn.getInt(0, 255), rn.getInt(0, 255), rn.getInt(0, 255));
		pBalls.push_back(new kineticBalls(vec2(_ball.getPos().x - _ball.getDeltaX(), _ball.getPos().y * _ball.getDeminution()), vec2(-ballVel.x, ballVel.y),
			ballsRaius[_ball.getStep()], ballColor, _ball.getStep(), ballsHp[_ball.getStep()]));
	}
	else 
	{
		ps.explode(_ball.getPos());

	}

}



//bool StageWalls::isImpact(Bullets& _bullet, kineticBalls& _ball) 
//{
//	const float distance = (_bullet.position - _ball.position).getMagnitude();
//	float twoRaius = _bullet.radius + _ball.radius;
//	if (distance <= twoRaius)
//	{
//		_ball.setHp(_ball.getHp() - _bullet.getImpact());
//		return true;
//	}
//	return false;
//}
