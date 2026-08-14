#include <Level/GameLevel.h>
#include <Game/Game.h>

int main()
{
	// 창 제목 설정.
	SetConsoleTitleA("BomberMan");

	Game game;
	game.Run();
}