#include "Explosion.h"
#include <Actor/Wall.h>
#include <Actor/BreakWall.h>

using namespace Craft;
Explosion::Explosion(const Craft::Vector2& position)
	: Actor("X",position,Color::Red)
{
}

void Explosion::Tick(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= 1.0f)	{
		Destroy();
	}
}

void Explosion::OnCollision(const std::shared_ptr<Actor>& other)
{
	super::OnCollision(other);

	if (other->IsTypeOf<Wall>() || other->IsTypeOf<BreakWall>())
	{
		Destroy();
	}
}
