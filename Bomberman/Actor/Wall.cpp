#include "Wall.h"

using namespace Craft;
Wall::Wall(const Craft::Vector2& position)
	: Actor("#", position, Color::White)
{
	sortingOrder = 0;
}
