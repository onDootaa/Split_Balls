#pragma once
#include "command.h"
#include "Game2D.h"

class InputHandler
{
public:
	Command* pCmdMoveLeft = nullptr;
	Command* pCmdMoveRight = nullptr;
	Command* pCmdShooting = nullptr;
	Command* pCmdJumping = nullptr;

public:
	InputHandler()
	{
		pCmdMoveLeft = new cmdMoveLeft;
		pCmdMoveRight = new cmdMoveRight;
		pCmdShooting = new cmdShooting;
		pCmdJumping = new cmdJumping;
		//pCmdReset = 
	}
	void connectKeyboard(Game2D* _ballGame, Actor& _actor, const float& _dt)
	{
		if (_ballGame->isKeyPressed(GLFW_KEY_LEFT)) pCmdMoveLeft->Execute(_actor, _dt); 

		if (_ballGame->isKeyPressed(GLFW_KEY_RIGHT)) pCmdMoveRight->Execute(_actor,_dt);

		if (_ballGame->isKeyPressed (GLFW_KEY_SPACE)) { 
			pCmdShooting->Execute(_actor, _dt); 
			//SoundEngine::getInstance()->playSound("cannon");// , true);
		}
		//if (_ballGame->isKeyReleased(GLFW_KEY_BACKSPACE))
		//	SoundEngine::getInstance()->stopSound("cannon");

		if (_ballGame->isKeyPressed(GLFW_KEY_UP)) pCmdJumping->Execute(_actor, _dt);

		
	}
};

