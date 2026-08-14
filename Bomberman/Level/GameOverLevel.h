#pragma once

#include <Level/Level.h>

class GameOverLevel : public Craft::Level
{
public:
	GameOverLevel();
protected:
	virtual void OnInitialized() override;
private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

