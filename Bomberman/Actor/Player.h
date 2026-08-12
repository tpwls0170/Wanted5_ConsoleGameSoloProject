#pragma once
#include <Actor/Actor.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)
		
public:
	Player(const Craft::Vector2& position);
	inline void DecreaseBombCount() { bombCount--; }
private:
	virtual void Tick(float deltaTime) override;
	void Move(Craft::Vector2& position, float deltaTime);
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

private:
	int bombCount = 0;
	int bombMaxCount = 1;
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float moveSpeed = 10.0f;
};

