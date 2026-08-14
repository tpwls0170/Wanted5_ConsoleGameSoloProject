#pragma once
#include <Level/Level.h>

class ClearLevel : public Craft::Level
{
public:
	ClearLevel();
protected:
	virtual void OnInitialized() override;
private:
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;
};

