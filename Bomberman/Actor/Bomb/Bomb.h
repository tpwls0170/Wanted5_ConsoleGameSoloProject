#pragma once
#include <Actor/Actor.h>
#include <Actor/Player.h>

class Bomb : public Craft::Actor
{
	TYPE_DECLARATIONS(Bomb, Actor)
public:
	Bomb(const Craft::Vector2& position);
	virtual void Tick(float deltaTime) override;
	inline void SetrOwnerPlayer(Player* newOwner) { ownerPlayer = newOwner; }
private:
	void Explode();
private:
	Player* ownerPlayer = nullptr;
	int range = 1;
	float explosionTimer = 2.5f;
	float elapsedTime = 0;
	float directions[];
};