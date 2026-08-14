#include "Game.h"
#include <Level/GameLevel.h>
#include <Level/MenuLevel.h>
#include <Level/TitleLevel.h>
#include <Level/ClearLevel.h>
#include <Level/GameOverLevel.h>

Game::Game()
{
	// 두 레벨 생성 및 배열에 추가.
	levelList.emplace_back(std::make_shared<TitleLevel>());
	levelList.emplace_back(std::make_shared<GameLevel>());
	levelList.emplace_back(std::make_shared<MenuLevel>());
	levelList.emplace_back(std::make_shared<ClearLevel>());
	levelList.emplace_back(std::make_shared<GameOverLevel>());

	// 시작 상태 설정.
	nextState = State::TitleMenu;

	// 게임 시작시 활성화할 레벨 설정.
	mainLevel = levelList[(int)nextState];
}

void Game::ToggleMenu(State currentState , State nextState)
{
	int stateIndex = static_cast<int>(nextState);
	// 레벨 설정 및 상태 값 업데이트.
	mainLevel = levelList[stateIndex];
	if (mainLevel->IsTypeOf<GameLevel>() && currentState != State::Menu)
	{
		auto gameLevel = std::dynamic_pointer_cast<GameLevel>(mainLevel);

		if (gameLevel)
		{
			gameLevel->ResetGame();
		}
	}
	this->nextState = static_cast<State>(stateIndex);
}