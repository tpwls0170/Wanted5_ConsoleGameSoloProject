#include "Player.h"
#include <Engine/Engine.h>
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <iostream>

using namespace Craft;
Player::Player(const Craft::Vector2& position)
	: Actor("P",position,Color::Green)
{

}

void Player::Tick(float deltaTime)
{
	// 상위 계층의 tick 호출.
	super::Tick(deltaTime);

	Vector2 newPosition = Craft::Vector2::Zero;

    if (Input::Get().GetKey(VK_RIGHT))
    {
        OutputDebugStringA("RIGHT\n");
        newPosition.x += 1;
    }

    if (Input::Get().GetKey(VK_LEFT))
    {
        OutputDebugStringA("LEFT\n");
        newPosition.x -= 1;
    }

    if (Input::Get().GetKey(VK_UP))
    {
        OutputDebugStringA("UP\n");
        newPosition.y -= 1;
    }

    if (Input::Get().GetKey(VK_DOWN))
    {
        OutputDebugStringA("DOWN\n");
        newPosition.y += 1;
    }

    Move(newPosition);
}

void Player::Move(Craft::Vector2 position)
{
	Vector2 newPosition = GetPosition();

	newPosition.x += position.x;
	newPosition.y += position.y;
	SetPosition(newPosition);
}
