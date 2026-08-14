#include "Enemy.h"
#include <Engine/Engine.h>
#include <Level/GameLevel.h>
#include <Actor/Bomb/Explosion.h>
#include <random>

using namespace Craft;
Enemy::Enemy(const Craft::Vector2& position)
	: Actor("E",position,Color::Red), 
    xPosition(static_cast<float>(position.x)),
    yPosition(static_cast<float>(position.y))
{}

void Enemy::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    elaspedTime += deltaTime;

    if (elaspedTime <= 0.2f)
        return;

    elaspedTime = 0.0f;

    std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());

    Vector2 direction = Vector2::Zero;

    // 플레이어 가져오기
    auto player = level->GetPlayerPosition();

    Vector2 enemyPosition = GetPosition();
    

    Vector2 playerPosition = Craft::Vector2::Zero;
    if (player != nullptr)
    {
       playerPosition = player->GetPosition();
    }

    // 플레이어와의 거리
    int distance =
        std::abs(enemyPosition.x - playerPosition.x) +
        std::abs(enemyPosition.y - playerPosition.y);

    // 플레이어 감지
    if (distance <= 10)
    {
        // --------------------
        // 추적
        // --------------------

        Vector2 diff = playerPosition - enemyPosition;

        if (std::abs(diff.x) > std::abs(diff.y))
        {
            direction.x = (diff.x > 0) ? 1 : -1;
        }
        else
        {
            direction.y = (diff.y > 0) ? 1 : -1;
        }
    }
    else
    {
        // --------------------
        // 랜덤 이동
        // --------------------

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<int> randMove(0, 4);

        int randomNum = randMove(gen);

        if (randomNum == 0)
            direction.x += 1;

        if (randomNum == 1)
            direction.x -= 1;

        if (randomNum == 2)
            direction.y -= 1;

        if (randomNum == 3)
            direction.y += 1;
    }

    // 이동 가능한지 확인
    Vector2 nextPosition = GetPosition() + direction;

    if (!level->CanMove(nextPosition))
    {
        direction = Vector2::Zero;
    }

    Move(direction, deltaTime);
}

void Enemy::Move(Craft::Vector2 & position, float deltaTime)
{
    xPosition += position.x * moveSpeed * deltaTime;
    yPosition += position.y * moveSpeed * deltaTime;

    if (xPosition < 0)
    {
        xPosition = 0.0;
    }

    if (yPosition < 0)
    {
        yPosition = 0.0;
    }

    if (xPosition + width >= Engine::Get().GetWidth())
    {
        xPosition = static_cast<float>(Engine::Get().GetWidth() - width);
    }

    if (yPosition + hight >= Engine::Get().GetHeight())
    {
        yPosition = static_cast<float>(Engine::Get().GetHeight() - hight);
    }

    Vector2 newPosition = GetPosition();

    newPosition.x = static_cast<int>(xPosition);
    newPosition.y = static_cast<int>(yPosition);

    SetPosition(newPosition);
}

void Enemy::OnCollision(const std::shared_ptr<Actor>&other)
{
    if (other->IsTypeOf<Explosion>())
    {
        std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
        level->DestoryEnemy();
        Destroy();
    }
}
