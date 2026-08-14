#pragma once
#include <Actor/Actor.h>

class Enemy : public Craft::Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)
public:
	Enemy(const Craft::Vector2& position);
private:
	virtual void Tick(float deltaTime) override;
	void Move(Craft::Vector2& position, float deltaTime);
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
private:
	float elaspedTime = 0.0f;
	float xPosition = 0.0f;
	float yPosition = 0.0f;
	float moveSpeed = 10.0f;
};

