#pragma once
#include <Actor/Actor.h>

class Explosion : public Craft::Actor
{
	TYPE_DECLARATIONS(Explosion, Actor)
public:
	Explosion(const Craft::Vector2& position);
	virtual void Tick(float deltaTime) override;
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
private:
	float elapsedTime = 0.0f;

};

