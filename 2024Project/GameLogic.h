#pragma once

// �÷��̾��� ������ ���Ҷ� ���� ������� �ϴ� �׸�������
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
	THIEF = 0, // ������(����)
	TAGGER = 1, // ����
};

typedef struct _tagPlayer {
	POS tPos; // ��ġ
	POS tNewPos; // �� Ȯ�ο�
	PLAYER_DIRECTION playerDir = PLAYER_DIRECTION::DOWN; // �÷��̾ ��� �ٶ󺸰� �ִ���
	PLAYER_ROLE playerRole; // �÷��̾��� ����
}PLAYER, *PPLAYER;

void Update(PPLAYER theif, PPLAYER tagger);
void Movement(PPLAYER theif, PPLAYER tagger);
void Render(PPLAYER theif, PPLAYER tagger);
void DelayTime();
PLAYER_DIRECTION CheckTheifDirection(PLAYER_DIRECTION playerDir);
PLAYER_DIRECTION CheckTaggerDirection(PLAYER_DIRECTION playerDir);