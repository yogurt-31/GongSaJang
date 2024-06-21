#pragma once
#include <time.h>
#include "Logic.h"

// �÷��̾��� ������ ���Ҷ� ���� ������� �ϴ� �׸�������
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
	THIEF = 0, // ������(����)
	TAGGER = 1, // ����
};

typedef struct _tagPlayer {
	POS tPos; // ��ġ
	POS tNewPos; // �� Ȯ�ο�
	POS tBeanPos; // ��� ���� ��ġ
	PLAYER_DIRECTION playerDir = PLAYER_DIRECTION::DOWN; // �÷��̾ ��� �ٶ󺸰� �ִ���
	PLAYER_ROLE playerRole; // �÷��̾��� ����
}PLAYER, *PPLAYER;

bool Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger);
void Movement(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger);
void PlayerMove(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER theif, PPLAYER tagger);
void CreateBean(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER tagger);
clock_t CreateItem(char _arrMap[MAP_HEIGHT][MAP_WIDTH], clock_t time);
void ItemEvent(PPLAYER theif, PPLAYER tagger);
PLAYER_DIRECTION CheckTheifDirection(PLAYER_DIRECTION playerDir);
PLAYER_DIRECTION CheckTaggerDirection(PLAYER_DIRECTION playerDir);