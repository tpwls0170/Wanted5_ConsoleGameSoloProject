#include "BreakWall.h"

using namespace Craft;
BreakWall::BreakWall(const Craft::Vector2& position)
	: Actor("+",position, Color::Cyan)
{
	sortingOrder = 0;
}
