#include "Bomb.h"
#include <Level/Level.h>
#include <Actor/Bomb/Explosion.h>
#include <Level/GameLevel.h>

using namespace Craft;
Bomb::Bomb(const Craft::Vector2& position, int range)
	: Actor("O",position,Color::Blue), range(range)
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

void Bomb::OnCollision(const std::shared_ptr<Actor>& other)
{
	if (other->IsTypeOf<Explosion>())
	{
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

		// 이동 처리를 위해 GameLevel 객체 얻어오기.
		// 다운 캐스팅 - 위험함 -> 형변환 실패하면 null 반환.
		std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(GetOwner());

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

				ExplosionResult result =
					gameLevel->CanExplosition(position);

				if (result == ExplosionResult::Wall)
					break;

				level->SpawnActor<Explosion>(position);

				if (result == ExplosionResult::BreakWall)
					break;
			}
		}
	}
}
