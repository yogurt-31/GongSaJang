#pragma once
#include "Logic.h"

// 플레이어의 방향을 구할때 쓰지 않을까요 일단 그리생각함
typedef struct _tagpos {
	int x;
	int y;

	bool operator ==(const _tagpos& _pos)
	{
		if (x == _pos.x && y == _pos.y)
			return true;
		else
			return false;
	}
}POS, *PPOS;

enum class PLAYER_DIRECTION {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
};

enum class PLAYER_ROLE {
	THIEF = 0, // 도망자(도둑)
	TAGGER = 1, // 술래
};

typedef struct _tagPlayer {
	POS tPos; // 위치
	POS tNewPos; // 벽 확인용
	POS tBeanPos; // 콩알 생성 위치
	PLAYER_DIRECTION playerDir = PLAYER_DIRECTION::DOWN; // 플레이어가 어디를 바라보고 있는지
	PLAYER_ROLE playerRole; // 플레이어의 역할
}PLAYER, *PPLAYER;

void Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger);
void Movement(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger);
void CreateBean(PPLAYER tagger);
PLAYER_DIRECTION CheckTheifDirection(PLAYER_DIRECTION playerDir);
PLAYER_DIRECTION CheckTaggerDirection(PLAYER_DIRECTION playerDir);