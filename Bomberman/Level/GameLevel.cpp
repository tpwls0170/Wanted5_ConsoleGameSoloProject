#include "GameLevel.h"
#include <Actor/Player.h>
#include <Actor/Enemy.h>
#include <Actor/Wall.h>
#include <Actor/BreakWall.h>
#include <Actor/Bomb/Bomb.h>
#include <cassert>

using namespace Craft;
void GameLevel::OnInitialized()
{
	Level::OnInitialized();
	LoadMap("BombermanMap.txt");
}

void GameLevel::LoadMap(const std::string & fileName)
{
	// 최종 경로 조립.
	std::string path = std::string("../Assets/") + fileName;

	// 파일 열기 (C-Style).
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");
	if (!file)
	{
		assert(false && "failed to open a sokoban stage file.");
		return;
	}

	// 파일의 내용을 저장할 버퍼(데이터 저장공간) 확인.
	// 파일 길이 확인 
	// -> 파일 위치를 제일 뒤로 이동 시킨 다음, 해당 위치 값 읽기.
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	// 파일 제일 끝위치를 구한 다음에는 다시 처음으로 되돌리기.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// 앞에서 구한 위치를 사용해서 버퍼 생성.
	char* buffer = new char[fileSize] {};

	// 데이터 읽기(파일 읽기).
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	// 어서트.
	assert(readSize > 0 && "No data is in the stage file.");
	std::vector<char> row;
	
	// 문자열에 저장된 값을 접근할 때 사용할 인덱스.
	int index = 0;

	Vector2 position;
	while (true)
	{
		// 종료 조건 - 내용을 모두 읽었는지 파악.
		if (index >= fileSize)
		{
			break;
		}

		// 이번에 확인할 문자 값.
		char mapCharacter = buffer[index];

		// 인덱스 증가 처리.
		++index;

		// 현재 문자가 개행 문자라면 로직은 건너뛰고,
		// 위치 값만 설정.
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;
			continue;
		}

		// 읽은 문자 별로 처리.
		switch (mapCharacter)
		{
			// 벽.
		case '#':
			// 벽 액터 생성.
			SpawnActor<Wall>(position);
			break;
			// 부서지는 벽
		case '+':
			SpawnActor<BreakWall>(position);
			break;

			// 플레이어.
		case 'p':
			OutputDebugStringA(
				("Player Position : "
					+ std::to_string(position.x)
					+ ", "
					+ std::to_string(position.y)
					+ "\n").c_str()
			);
			// 플레이어 액터 생성.
			SpawnActor<Player>(position);
			break;
			// 적
		case 'e':
			SpawnActor<Enemy>(position);
			break;
		}

		// x 위치 업데이트.
		++position.x;
	}

	// 모두 사용한 버퍼 해제.
	delete[] buffer;
	buffer = nullptr;

	// 파일 닫기.
	fclose(file);
	file = nullptr;
}

bool GameLevel::CanMove(const Craft::Vector2& nextPosition)
{
	if (isGameClear)
		return false;

	std::vector<std::shared_ptr<Actor>> wallList;

	for (const std::shared_ptr<Actor>& actor : actorList)
	{
		if (actor->IsTypeOf<Wall>() ||
			actor->IsTypeOf<BreakWall>())
		{
			if (actor->GetPosition() == nextPosition)
			{
				return false;
			}
		}
	}

	return true;
}