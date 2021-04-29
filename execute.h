#pragma once
#include <iostream>
#include "stageWalls.h"
#include "InputHandler.h"
//#include <string>


class Execute : public Game2D
{
private:
	StageWalls wall;
	InputHandler inputHandler;
	//const int screenWidth = 1024;
	//const int screenHeight = 768;
	std::string title = "Split Balls Game";
	bool isFullscreen = false;

public:

	Execute()
		: Game2D("Balls Split", 1024, 768, false, 0)
	{
		if(!isFullscreen)
		{
		wall.setHalfHeight(Game2D::getWidth() / 768.0f) ;
		wall.setbB_y(wall.getbB_y() + wall.getStageBoxHeight());//(wall.getbBy + wall.getStageBoxHeight();
		}
		//std::cout << "width = " << Game2D::getWidth() << std::endl;
	}
	~Execute()
	{}
	void update()
	{
		float dt = getTimeStep() * 0.65f;
		wall.draw();
		wall.update(dt);
		inputHandler.connectKeyboard(this, wall.myCharactor, dt);
		if (this->isKeyPressedAndReleased(GLFW_KEY_R)) { wall.reset(); }
		if (this->isKeyPressedAndReleased(GLFW_KEY_N)) { wall.newBall(); }
	}
};