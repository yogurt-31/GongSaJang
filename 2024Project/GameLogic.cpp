#include <Windows.h>
#include <algorithm>
#include "GameLogic.h"
#include "console.h"

void Update(PPLAYER theif, PPLAYER tagger)
{
	theif->playerDir = CheckTheifDirection(theif->playerDir);
	tagger->playerDir = CheckTaggerDirection(tagger->playerDir);
	Movement(theif, tagger);
	Render(theif, tagger);
}

void Movement(PPLAYER theif, PPLAYER tagger)
{
	theif->tNewPos = theif->tPos;
	tagger->tNewPos = tagger->tPos;

	// 도둑 위치
	switch (theif->playerDir)
	{
	case PLAYER_DIRECTION::UP:
		--theif->tNewPos.y;
		break;
	case PLAYER_DIRECTION::DOWN:
		++theif->tNewPos.y;
		break;
	case PLAYER_DIRECTION::LEFT:
		--theif->tNewPos.x;
		break;
	case PLAYER_DIRECTION::RIGHT:
		++theif->tNewPos.x;
		break;
	}

	// 술래 위치
	switch (tagger->playerDir)
	{
	case PLAYER_DIRECTION::UP:
		--tagger->tNewPos.y;
		break;
	case PLAYER_DIRECTION::DOWN:
		++tagger->tNewPos.y;
		break;
	case PLAYER_DIRECTION::LEFT:
		--tagger->tNewPos.x;
		break;
	case PLAYER_DIRECTION::RIGHT:
		++tagger->tNewPos.x;
		break;
	}

	// 벽 감지
	/*if (_arrmap[_pPlayer->tNewPos.y][_pPlayer->tNewPos.x]
		!= (char)OBJ_TYPE::WALL)
	{
		_pPlayer->tPos = _pPlayer->tNewPos;
	}*/

	theif->tPos = theif->tNewPos;
	tagger->tPos = tagger->tNewPos;
}

void Render(PPLAYER theif, PPLAYER tagger)
{
	DelayTime();
	Gotoxy(theif->tPos.x * 2, theif->tPos.y);
	cout << "☆";
	Gotoxy(tagger->tPos.x * 2, tagger->tPos.y);
	cout << "★";
	CreateBean(tagger);

}

PLAYER_DIRECTION CheckTheifDirection(PLAYER_DIRECTION playerDir)
{
	PLAYER_DIRECTION dir = playerDir;
	// 키보드 입력으로 방향 확인
	if (GetAsyncKeyState('W') & 0x8000)
		dir = PLAYER_DIRECTION::UP;
	else if (GetAsyncKeyState('S') & 0x8000)
		dir = PLAYER_DIRECTION::DOWN;
	else if (GetAsyncKeyState('A') & 0x8000)
		dir = PLAYER_DIRECTION::LEFT;
	else if (GetAsyncKeyState('D') & 0x8000)
		dir = PLAYER_DIRECTION::RIGHT;

	return dir;
}

PLAYER_DIRECTION CheckTaggerDirection(PLAYER_DIRECTION playerDir)
{
	PLAYER_DIRECTION dir = playerDir;
	// 키보드 입력으로 방향 확인
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		dir = PLAYER_DIRECTION::UP;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		dir = PLAYER_DIRECTION::DOWN;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		dir = PLAYER_DIRECTION::LEFT;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		dir = PLAYER_DIRECTION::RIGHT;

	return dir;
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

void CreateBean(PPLAYER tagger)
{
	int xValue = tagger->tBeanPos.x - tagger->tPos.x;
	int yValue = tagger->tBeanPos.y - tagger->tPos.y;

	if (xValue < 0) xValue *= -1;
	if (yValue < 0) yValue *= -1;

	if (xValue + yValue >= 5) {
		tagger->tBeanPos = tagger->tPos;
		// 나는 콩을 생성할테야
		Gotoxy(tagger->tPos.x * 2, tagger->tPos.y);
		cout << "♭";
	}
}
