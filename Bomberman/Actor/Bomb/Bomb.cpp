#include "Bomb.h"
#include <Level/Level.h>
#include <Actor/Bomb/Explosion.h>

using namespace Craft;
Bomb::Bomb(const Craft::Vector2& position)
	: Actor("O",position,Color::Blue)
{

}

void Bomb::Tick(float deltaTime)
{
	elapsedTime += deltaTime;

	if (elapsedTime >= explosionTimer)
	{
		elapsedTime = 0;
		Explode();
	}
}

void Bomb::Explode()
{
	if (ownerPlayer != nullptr)
	{
		ownerPlayer->DecreaseBombCount();
		this->Destroy();
		auto level = GetOwner();

		Vector2 directions[] =
		{
			Vector2(1, 0),
			Vector2(-1, 0),
			Vector2(0, 1),
			Vector2(0,-1)
		};

		level->SpawnActor<Explosion>(GetPosition());
		for (const Vector2& direction : directions)
		{
			for (int i = 1; i <= range; ++i)
			{
				Vector2 position = GetPosition();

				position.x += direction.x * i;
				position.y += direction.y * i;

				level->SpawnActor<Explosion>(position);
			}
		}
	}
}
