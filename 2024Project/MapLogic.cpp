#include<Windows.h>
#include<mmsystem.h>
#include<algorithm>
#include<fstream>
#include "MapLogic.h"
#include "console.h"
#pragma comment(lib, "winmm.lib")

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPOS _pStartPos, PPOS _pEndPos)
{
	system("title 22Bombman | mode con cols=110 lines=30");
	CursorVis(false, 1);
	LockResize();
	//PlayBgm(TEXT("cozycoffeehouse.mp3"), 100); // 10(1%), 100(10%), 1000(100%)
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
	//*_pPlayer = { *_pStartPos, {}, 0,1, false ,false, false };
}

void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _thief, PPLAYER _tagger)
{
	DelayTime();
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_thief->tPos.x == j && _thief->tPos.y == i)
				cout << "★";
			else if (_tagger->tPos.x == j && _tagger->tPos.y == i)
				cout << "☆";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
				cout << "■";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD)
				cout << "  ";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::BEAN)
				cout << "♭";
			SetColor((int)COLOR::WHITE);
		}
		cout << endl;
	}
	cout << "방향키 : 술래 움직임" << endl;
	cout << "WASD  : 도둑 움직임" << endl;
}

void DelayTime()
{
	clock_t oldtime, curtime;
	oldtime = clock();

	while (true)
	{
		curtime = clock();
		if (curtime - oldtime > 100)
		{
			oldtime = curtime;
			break;
		}
	}
}