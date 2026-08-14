#include "GameOverLevel.h"
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>

using namespace Craft;
GameOverLevel::GameOverLevel()
{}

void GameOverLevel::OnInitialized()
{
	Level::OnInitialized();
	Draw();
}

void GameOverLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu(State::GameOver, State::TitleMenu);
		return;
	}
}

void GameOverLevel::Draw()
{
	const std::vector<std::string> gameOverScreen =
	{
		"+--------------------------------------+",
		"|                                      |",
		"|                                      |",
		"|          G A M E   O V E R          |",
		"|                                      |",
		"|             __________               |",
		"|            /          \\              |",
		"|           /   OH NO!   \\             |",
		"|           \\            /             |",
		"|            \\__________/              |",
		"|                                      |",
		"|             YOU LOST!                |",
		"|                                      |",
		"|             X     X                  |",
		"|               ___                    |",
		"|              /   \\                   |",
		"|             | RIP |                  |",
		"|              \\___/                   |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|          +----------------+          |",
		"|          |    Main menu   |          |",
		"|          +----------------+          |",
		"|                                      |",
		"|             Press ENTER              |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"+--------------------------------------+"
	};

	for (int iy = 0; iy < static_cast<int>(gameOverScreen.size()); ++iy)
	{
		Renderer::Get().Submit(
			gameOverScreen[iy],
			Vector2(0, iy)
		);
	}
}
