#pragma once
#include "actor.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void Execute(Actor& actor, const float& _dt) = 0;
};

class cmdMoveLeft : public Command
{
public:
	void Execute(Actor& _actor, const float& _dt) override
	{
		_actor.moveLeft(_dt);
	}
};
class cmdMoveRight : public Command
{
public:
	void Execute(Actor& _actor, const float& _dt) override
	{
		_actor.moveRight(_dt);
	}
};
class cmdShooting : public Command
{
public:
	void Execute(Actor& _actor, const float& _dt) override
	{
		_actor.shooting(_dt);
	}
};
class cmdJumping : public Command
{
public:
	void Execute(Actor& _actor, const float& _dt) override
	{
		_actor.jumping(_dt);
	}
};