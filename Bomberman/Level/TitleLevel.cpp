#include "TitleLevel.h"
#include <Game/Game.h>
#include <Input/Input.h>
#include <Render/Renderer.h>
#include <cassert>

using namespace Craft;
TitleLevel::TitleLevel()
{
	// 메뉴 아이템 생성.
	itemList.emplace_back(
		std::make_unique<TitleItem>(
			"Start Game",
			[]()
	{
		// 메뉴 토글 함수 호출.
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu(State::TitleMenu, State::GamePlay);
	}
		)
	);

	itemList.emplace_back(
		std::make_unique<TitleItem>(
			"Quit Game",
			[]()
	{
		// 게임 종료 호출.
		Engine::Get().Quit();
	}
		)
	);
}

void TitleLevel::OnInitialized()
{
	Level::OnInitialized();
	Draw();
}

void TitleLevel::Tick(float deltaTime)
{
	Level::Tick(deltaTime);

	// 배열의 요소 개수.
	const int length = static_cast<int>(itemList.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// 인덱스 돌리기 (-방향).
		currentIndex = (currentIndex - 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// 인덱스 돌리기 (+방향).
		currentIndex = (currentIndex + 1) % length;
	}

	// 엔터 입력 처리 -> 현재 선택된 메뉴의 로직 실행.
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		// 어써트.
		assert(currentIndex >= 0
			&& currentIndex < (int)itemList.size()
			&& itemList[currentIndex]->onSelected
		);

		// 메뉴 아이템에 저장된 로직 실행.
		itemList[currentIndex]->onSelected();
	}
}

void TitleLevel::Draw()
{
	// 40 x 30 화면에 맞춘 타이틀.
	const std::vector<std::string> title =
	{
		"+--------------------------------------+",
		"|                                      |",
		"|          C++ CONSOLE GAME            |",
		"|                                      |",
		"|          *    *    *    *            |",
		"|                                      |",
		"|             BOMBERMAN                |",
		"|                                      |",
		"|             BOOM!                    |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"|                                      |",
		"+--------------------------------------+"
	};

	// 타이틀 출력.
	for (int iy = 0; iy < static_cast<int>(title.size()); ++iy)
	{
		Renderer::Get().Submit(
			title[iy],
			Vector2::Zero + Vector2(0, iy)
		);
	}

	// 메뉴 아이템 출력.
	const int count = static_cast<int>(itemList.size());

	for (int ix = 0; ix < count; ++ix)
	{
		Color textColor = (ix == currentIndex)
			? selectedColor
			: unselectedColor;

		Renderer::Get().Submit(
			itemList[ix]->text,
			Vector2(14, 13 + ix),
			textColor
		);
	}

	// 안내 문구.
	Renderer::Get().Submit(
		"UP / DOWN : Select",
		Vector2(10, 20)
	);

	Renderer::Get().Submit(
		"ENTER : Confirm",
		Vector2(12, 22)
	);
}