#pragma once
#include <Actor/Actor.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)
		
public:
	Player(const Craft::Vector2& position);
	void DecreaseBombCount();
private:
	virtual void Tick(float deltaTime) override;
	void Move(float directionX, float directionY, float deltaTime);

private:
	int bombCount = 0;
	int bombMaxCount = 1;
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float moveSpeed = 10.0f;
};

