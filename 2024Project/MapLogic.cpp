#include<Windows.h>
#include<fstream>
#include "MapLogic.h"
#include "console.h"
#pragma comment(lib, "winmm.lib")

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH])
{
	system("title Run! Catch! | mode con cols=110 lines=30");
	CursorVis(false, 1);
	LockResize();
	SetFontSize(FW_BOLD, 20, 20);
	// 내부 맵찍기, 외부 맵찍기(파일입출력 - json, tiled)
	// 파일입출력.
	std::fstream readMap("stage.txt");
	if (readMap.is_open())
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			// 다시 getline으로 파일을 읽을 때 기존꺼
			// clear해줘야함. 여러 스테이지의 경우.
			//readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail())
			{
				std::cout << "file error" << endl;
			}
		}
	}
}

void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _thief, PPLAYER _tagger)
{
	DelayTime(100);

	if (_thief->playerRole != PLAYER_ROLE::THIEF) {
		PPLAYER player = _thief;
		_thief = _tagger;
		_tagger = player;
	}
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_thief->tPos.x == j && _thief->tPos.y == i)
				cout << "☆";
			else if (_tagger->tPos.x == j && _tagger->tPos.y == i)
				cout << "★";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
				cout << "■";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD)
				cout << "  ";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ITEM_CHANGE)
				cout << "□";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::BEAN)
				cout << "♭";
			SetColor((int)COLOR::WHITE);
		}
		cout << endl;
	}
	cout << "플레이어 1 : 방향키" << endl;
	cout << "플레이어 2 : WASD" << endl;
	cout << "☆ : 도둑" << endl;
	cout << "★ : 술래" << endl;
}

int BeanCount(char _arrMap[MAP_HEIGHT][MAP_WIDTH])
{
	int cnt = 0;
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_arrMap[i][j] == (char)OBJ_TYPE::BEAN)
				cnt++;
		}
	}
	return cnt;
}

void DelayTime(int time)
{
	clock_t oldtime, curtime;
	oldtime = clock();

	while (true)
	{
		curtime = clock();
		if (curtime - oldtime > time)
		{
			oldtime = curtime;
			break;
		}
	}
}