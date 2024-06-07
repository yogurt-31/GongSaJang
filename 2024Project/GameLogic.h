#pragma once

// 플레이어의 방향을 구할때 쓰지 않을까요 일단 그리생각함
typedef struct _tagpos {
	int x;
	int y;
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
	PLAYER_DIRECTION playerDir = PLAYER_DIRECTION::DOWN; // 플레이어가 어디를 바라보고 있는지
	PLAYER_ROLE playerRole; // 플레이어의 역할
}PLAYER, *PPLAYER;

void Update(PPLAYER theif, PPLAYER tagger);
void Movement(PPLAYER theif, PPLAYER tagger);
void Render(PPLAYER theif, PPLAYER tagger);
void DelayTime();
PLAYER_DIRECTION CheckTheifDirection(PLAYER_DIRECTION playerDir);
PLAYER_DIRECTION CheckTaggerDirection(PLAYER_DIRECTION playerDir);