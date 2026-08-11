#pragma once
#include <Actor/Actor.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)
		
public:
	Player(const Craft::Vector2& position);
private:
	virtual void Tick(float deltaTime) override;
	void Move(Craft::Vector2 position);

private:
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float moveSpeed = 50.0f;
};

