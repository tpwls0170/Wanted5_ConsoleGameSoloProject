#pragma once
#include <Level/Level.h>

class GameLevel : public Craft::Level
{
private:
	virtual void OnInitialized();
	void LoadMap(const std::string& fileName);
private:
	bool isGameClear = false;
};

