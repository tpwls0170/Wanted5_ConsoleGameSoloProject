#include "ClearLevel.h"
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

using namespace Craft;
ClearLevel::ClearLevel()
{}

void ClearLevel::OnInitialized()
{
	Level::OnInitialized();
	Draw();
}

void ClearLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}
}

void ClearLevel::Draw()
{
	const std::vector<std::string> clearScreen =
	{
		"+--------------------------------------+",
		"|                                      |",
		"|                                      |",
		"|          G A M E   C L E A R         |",
		"|                                      |",
		"|             __________               |",
		"|            /          \\              |",
		"|           /   YOU WIN! \\             |",
		"|           \\            /             |",
		"|            \\__________/              |",
		"|                                      |",
		"|          *** CONGRATULATIONS ***     |",
		"|                                      |",
		"|        *       *       *             |",
		"|          \\     |     /               |",
		"|        ---   BOOM!   ---             |",
		"|          /     |     \\               |",
		"|        *       *       *             |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"+--------------------------------------+"
	};

	for (int iy = 0; iy < static_cast<int>(clearScreen.size()); ++iy)
	{
		Renderer::Get().Submit(
			clearScreen[iy],
			Vector2(0, iy)
		);
	}
}
