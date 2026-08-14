#include "Player.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Actor/Bomb/Bomb.h>
#include <Actor/Bomb/Explosion.h>
#include <Actor/BreakWall.h>
#include <Actor/Enemy.h>
#include <Actor/Wall.h>
#include <Game/Game.h>

using namespace Craft;
Player::Player(const Craft::Vector2& position)
	: Actor("P",position,Color::Green), 
    xPosition(static_cast<float>(position.x)),
    yPosition(static_cast<float>(position.y))
{
    sortingOrder = 10;
}

void Player::IncreaseBombRange()
{
    if (bombRange >= 10)
        return;

    bombRange++;
}

void Player::Tick(float deltaTime)
{
	// 상위 계층의 tick 호출.
	super::Tick(deltaTime);

    // ESC 종료 처리.
    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        // 메뉴 토글.
        Game& game = dynamic_cast<Game&>(Engine::Get());
        game.ToggleMenu();
        return;
    }

    // 이동 처리를 위해 GameLevel 객체 얻어오기.
   // 다운 캐스팅 - 위험함 -> 형변환 실패하면 null 반환.
    std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());

    Vector2 direction = Craft::Vector2::Zero;

    if (Input::Get().GetKey(VK_RIGHT))
    {
        direction.x += 1;
    }

    if (Input::Get().GetKey(VK_LEFT))
    {
        direction.x -= 1;
    }

    if (Input::Get().GetKey(VK_UP))
    {
        direction.y -= 1;
    }

    if (Input::Get().GetKey(VK_DOWN))
    {
        direction.y += 1;
    }
    Vector2 nextPosition = GetPosition() + direction;

    if (!level->CanMove(nextPosition))
    {
        direction = Vector2::Zero;
    }

    if (Input::Get().GetKeyDown(VK_SPACE))
    {
        if (bombCount < bombMaxCount)
        {
            auto level = GetOwner().get();
            auto bomb = level->SpawnActor<Bomb>(position,bombRange);
            bomb->SetrOwnerPlayer(this);
            bombCount++;
        }
    }

    Move(direction, deltaTime);
}

void Player::Move(Craft::Vector2& position, float deltaTime)
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

void Player::OnCollision(const std::shared_ptr<Actor>& other)
{
    super::OnCollision(other);

    if (other->IsTypeOf<Explosion>() || other->IsTypeOf<Enemy>())
    {
        Destroy();
        QuitGame();
    }
}