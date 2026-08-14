#include "BreakWall.h"
#include <Actor/Bomb/Explosion.h>
#include <Level/GameLevel.h>

using namespace Craft;
BreakWall::BreakWall(const Craft::Vector2& position)
	: Actor("+",position, Color::Cyan)
{
	sortingOrder = 0;
}

void BreakWall::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);

    if (other->IsTypeOf<Explosion>())
    {
        Destroy();
        // 이동 처리를 위해 GameLevel 객체 얻어오기.
        // 다운 캐스팅 - 위험함 -> 형변환 실패하면 null 반환.
        std::shared_ptr<GameLevel> gameLevel = Cast<GameLevel>(GetOwner());

        gameLevel->DestoryBreakWall(GetPosition());
    }
}
