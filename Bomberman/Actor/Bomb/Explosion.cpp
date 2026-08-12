#include "Explosion.h"

using namespace Craft;
Explosion::Explosion(const Craft::Vector2& position)
	: Actor("X",position,Color::Red)
{
}

void Explosion::Tick(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= 2)
	{
		Destroy();
	}
}
