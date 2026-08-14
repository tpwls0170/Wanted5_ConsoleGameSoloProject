#pragma once
#include <Level/Level.h>

enum class ExplosionResult
{
	CanExplode,
	Wall,
	BreakWall
};

class GameLevel : public Craft::Level
{
public:
	bool CanMove(const Craft::Vector2& nextPosition);
	ExplosionResult CanExplosition(const Craft::Vector2& nextPosition);
	void DestoryBreakWall(const Craft::Vector2& position);

	std::shared_ptr<Craft::Actor> GetPlayerPosition();
private:
	virtual void OnInitialized();
	void LoadMap(const std::string& fileName);
private:
	bool isGameClear = false;
};

