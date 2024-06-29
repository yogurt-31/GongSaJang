#include <Windows.h>
#include <algorithm>
#include "GameLogic.h"
#include "MapLogic.h"
#include "console.h"

std::string Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger)
{
	
	theif->playerDir = CheckTheifDirection(theif->playerDir);
	tagger->playerDir = CheckTaggerDirection(tagger->playerDir);
	Movement(_arrMap, theif, tagger);

	int beanCnt = BeanCount(_arrMap);
	// 승리
	if (theif->tPos == tagger->tPos) {
		return "술래가 이겼습니다!";
	}
	if (beanCnt <= 0) {
		return "도둑이 이겼습니다!";
	}
	else return "";
}

void Movement(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger)
{
	theif->tNewPos = theif->tPos;
	tagger->tNewPos = tagger->tPos;

	// 도둑 위치
	if (theif->playerRole == PLAYER_ROLE::THIEF) {
		PlayerMove(_arrMap, theif, tagger);
	}
	else {
		PlayerMove(_arrMap, tagger, theif);
	}
}

void PlayerMove(char arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger)
{
	#pragma region 움직임

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

	#pragma endregion

	#pragma region 벽 감지

	if (arrMap[theif->tNewPos.y][theif->tNewPos.x] != (char)OBJ_TYPE::WALL)
	{
		theif->tPos = theif->tNewPos;
	}

	if (arrMap[tagger->tNewPos.y][tagger->tNewPos.x] != (char)OBJ_TYPE::WALL)
	{
		tagger->tPos = tagger->tNewPos;
	}

	#pragma endregion


	#pragma region 아이템 획득

	if (arrMap[theif->tPos.y][theif->tPos.x] == (char)OBJ_TYPE::ITEM_CHANGE) {
		arrMap[theif->tPos.y][theif->tPos.x] = (char)OBJ_TYPE::ROAD;
		ItemEvent(theif, tagger);
	}

	else if (arrMap[tagger->tPos.y][tagger->tPos.x] == (char)OBJ_TYPE::ITEM_CHANGE) {
		arrMap[tagger->tPos.y][tagger->tPos.x] = (char)OBJ_TYPE::ROAD;
		ItemEvent(theif, tagger);
	}

	arrMap[theif->tPos.y][theif->tPos.x] = (char)OBJ_TYPE::ROAD;
	#pragma endregion

	// 콩알 생성
	CreateBean(arrMap, tagger);
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
		_arrMap[tagger->tBeanPos.y][tagger->tBeanPos.x] = (char)OBJ_TYPE::BEAN;
	}
}

clock_t CreateItem(char _arrMap[MAP_HEIGHT][MAP_WIDTH], clock_t currentTime)
{
	srand((unsigned int)time(NULL));
	clock_t nowTime = clock();
	if (nowTime - currentTime >= 10000) {
		int randX = 0, randY = 0;
		while (_arrMap[randY][randX] != (char)OBJ_TYPE::ROAD 
			&& _arrMap[randY][randX] != (char)OBJ_TYPE::BEAN) {
			randX = rand() % MAP_WIDTH;
			randY = rand() % MAP_HEIGHT;
		}
		_arrMap[randY][randX] = (char)OBJ_TYPE::ITEM_CHANGE;
		return nowTime;
	}
	return currentTime;
}

void ItemEvent(PPLAYER theif, PPLAYER tagger)
{
	PLAYER_ROLE role = theif->playerRole;
	theif->playerRole = tagger->playerRole;
	tagger->playerRole = role;
}
