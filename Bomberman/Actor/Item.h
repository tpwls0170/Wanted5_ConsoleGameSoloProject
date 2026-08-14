#pragma once
#include <Actor/Actor.h>

class Item : public Craft::Actor
{
	TYPE_DECLARATIONS(Item, Actor)	
public:
	Item(const Craft::Vector2& position, std::string itemName);
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
	std::string GetItemImage(std::string itemName);
	Craft::Color GetItemColor(std::string itemName);
private :
	std::string itemName;
};