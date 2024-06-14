#include<Windows.h>
#include<mmsystem.h>
#include<algorithm>
#include<fstream>
#include "MapLogic.h"
#include "console.h"
#pragma comment(lib, "winmm.lib")

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPOS _pStartPos, PPOS _pEndPos)
{
	system("title 22Bombman | mode con cols=80 lines=40");
	FullScreen();
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



	// 내부
	//strcpy_s(_arrMap[0], "21111100000000000000");
	//strcpy_s(_arrMap[1], "00000111111110000000");
	//strcpy_s(_arrMap[2], "00111100000000000000");
	//strcpy_s(_arrMap[3], "00000100000000000000");
	//strcpy_s(_arrMap[4], "00000111111111100000");
	//strcpy_s(_arrMap[5], "00000100000000100000");
	//strcpy_s(_arrMap[6], "00000100000000100000");
	//strcpy_s(_arrMap[7], "00000100000000100000");
	//strcpy_s(_arrMap[8], "00000100000000100000");
	//strcpy_s(_arrMap[9], "00000100000000100000");
	//strcpy_s(_arrMap[10],"00000100000000111100");
	//strcpy_s(_arrMap[11],"00000100000000000000");
	//strcpy_s(_arrMap[12],"00000111111111111100");
	//strcpy_s(_arrMap[13],"00000100000000001103");
	//strcpy_s(_arrMap[14],"00000100000000001001");
	//strcpy_s(_arrMap[15],"00000100000000001111");
	//strcpy_s(_arrMap[16],"00000100000000000000");
	//strcpy_s(_arrMap[17],"00000100000000000100");
	//strcpy_s(_arrMap[18],"00000111111111111100");
	//strcpy_s(_arrMap[19],"00000000000000000000");

	// 시작위치, 끝 위치 세팅.
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_arrMap[i][j] == (char)OBJ_TYPE::START)
				*_pStartPos = { j,i }; // { } 
			//	_pStartPos->x = j;
			//(*_pStartPos).x = j;
			else if (_arrMap[i][j] == (char)OBJ_TYPE::GOAL)
				*_pEndPos = { j,i }; // { } 
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
			else if (_arrMap[i][j] == (char)OBJ_TYPE::START)
				cout << "★";
			else if (_arrMap[i][j] == (char)OBJ_TYPE::GOAL)
				cout << "♨";
			SetColor((int)COLOR::WHITE);
		}
		cout << endl;
	}
	cout << "방향키: 움직임" << endl;
	cout << "Spacebar: 폭탄 설치" << endl;
	cout << "F: Push 온오프" << endl;
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