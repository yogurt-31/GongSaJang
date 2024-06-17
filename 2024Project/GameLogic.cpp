#include <Windows.h>
#include <algorithm>
#include "MapLogic.h"
#include "console.h"
#include "GameOver.h"

	bool Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger)
	{
		theif->playerDir = CheckTheifDirection(theif->playerDir);
		tagger->playerDir = CheckTaggerDirection(tagger->playerDir);
		Movement(_arrMap, theif, tagger);
		if (theif->tPos == tagger->tPos) {
			GameOver("술래 승리!");
			return false;
		}
		else return true;
	}

void Movement(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger)
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
	if (_arrMap[theif->tNewPos.y][theif->tNewPos.x]
		!= (char)OBJ_TYPE::WALL)
	{
		_arrMap[theif->tPos.y][theif->tPos.x] = (char)OBJ_TYPE::ROAD;
		theif->tPos = theif->tNewPos;
	}

	if (_arrMap[tagger->tNewPos.y][tagger->tNewPos.x]
		!= (char)OBJ_TYPE::WALL)
	{
		tagger->tPos = tagger->tNewPos;
	}
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

void CreateBean(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER tagger)
{
	int xValue = tagger->tBeanPos.x - tagger->tPos.x;
	int yValue = tagger->tBeanPos.y - tagger->tPos.y;

	if (xValue < 0) xValue *= -1;
	if (yValue < 0) yValue *= -1;

	if (xValue + yValue >= 5) {
		tagger->tBeanPos = tagger->tPos;
		// 나는 콩을 생성할테야
	}

	_arrMap[tagger->tBeanPos.y][tagger->tBeanPos.x] = (char)OBJ_TYPE::BEAN;
}
