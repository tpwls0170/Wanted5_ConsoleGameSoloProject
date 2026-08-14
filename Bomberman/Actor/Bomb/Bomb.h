#pragma once
#include <Actor/Actor.h>
#include <Actor/Player.h>

class Bomb : public Craft::Actor
{
	TYPE_DECLARATIONS(Bomb, Actor)
public:
	Bomb(const Craft::Vector2& position, int range);
	virtual void Tick(float deltaTime) override;
	inline void SetrOwnerPlayer(Player* newOwner) { ownerPlayer = newOwner; }
	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;
private:
	void Explode();
private:
	Player* ownerPlayer = nullptr;
	int range = 1;
	float explosionTimer = 2.5f;
	float elapsedTime = 0;
};