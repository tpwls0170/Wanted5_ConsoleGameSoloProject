#include "Item.h"
#include <Actor/Player.h>
#include <Actor/Bomb/Explosion.h>

using namespace Craft;
Item::Item(const Craft::Vector2& position, std::string itemName)
	: Actor(GetItemImage(itemName), position, GetItemColor(itemName))
	, itemName(itemName)
{}


void Item::OnCollision(const std::shared_ptr<Actor>& other)
{
	if (other->IsTypeOf<Explosion>())
	{
		this->Destroy();
	}
	
	if (other->IsTypeOf<Player>())
	{
		this->Destroy();
		auto player = Cast<Player>(other);

		if (this->itemName == "Range")
		{
			player->IncreaseBombRange();
		}
		else if (this->itemName == "Count")
		{
			player->IncreaseBombMaxCount();
		}
	}
}

std::string Item::GetItemImage(std::string itemName)
{
	if (itemName == "Range")
	{
		return "@";
	}
	else if (itemName == "Count")
	{
		return "$";
	}

	return "?";
}

Craft::Color Item::GetItemColor(std::string itemName)
{
	if (itemName == "Range")
	{
		return Color::Yellow;
	}
	else if (itemName == "Count")
	{
		return Color::Purple;
	}

	return Color::White;
}

