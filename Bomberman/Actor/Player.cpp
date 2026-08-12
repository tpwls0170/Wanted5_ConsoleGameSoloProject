#include "Player.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Actor/Bomb/Bomb.h>

using namespace Craft;
Player::Player(const Craft::Vector2& position)
	: Actor("P",position,Color::Green)
{
    sortingOrder = 10;
}

void Player::Tick(float deltaTime)
{
	// 상위 계층의 tick 호출.
	super::Tick(deltaTime);

    float directionX = 0.0f;
    float directionY = 0.0f;

    if (Input::Get().GetKey(VK_RIGHT))
    {
        directionX += 1;
    }

    if (Input::Get().GetKey(VK_LEFT))
    {
        directionX -= 1;
    }

    if (Input::Get().GetKey(VK_UP))
    {
        directionY -= 1;
    }

    if (Input::Get().GetKey(VK_DOWN))
    {
        directionY += 1;
    }

    if (Input::Get().GetKey(VK_SPACE))
    {
        if (bombCount < bombMaxCount)
        {
            auto level = GetOwner().get();
            auto bomb = level->SpawnActor<Bomb>(position);
            bomb->SetrOwnerPlayer(this);
            bombCount++;
        }
    }

    Move(directionX, directionY, deltaTime);
}

void Player::Move(float directionX, float directionY, float deltaTime)
{
    xPosition += directionX * moveSpeed * deltaTime;
    yPosition += directionY * moveSpeed * deltaTime;

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

void Player::DecreaseBombCount()
{
    bombCount--;
}
