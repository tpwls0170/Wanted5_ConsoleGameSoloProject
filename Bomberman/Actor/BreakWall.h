#pragma once
#include <Actor/Actor.h>

class BreakWall : public Craft::Actor
{
	TYPE_DECLARATIONS(BreakWall, Actor)

public:
	BreakWall(const Craft::Vector2& position);
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
};

