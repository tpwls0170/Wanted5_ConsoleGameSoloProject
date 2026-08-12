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
		level->SpawnActor<Explosion>(GetPosition());
	}
}
