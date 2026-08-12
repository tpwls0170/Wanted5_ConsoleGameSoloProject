#pragma once
#include <Level/Level.h>

class GameLevel : public Craft::Level
{
public:
	bool CanMove(const Craft::Vector2& nextPosition);
private:
	virtual void OnInitialized();
	void LoadMap(const std::string& fileName);
private:
	bool isGameClear = false;
};

