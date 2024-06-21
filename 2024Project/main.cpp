#include<Windows.h>
#include<fstream>
#include<string>

#include "console.h"
#include "TitleScene.h"
#include "PlayerLogic.h"
#include "MapLogic.h"

int main()
{
	char arrMap[MAP_HEIGHT][MAP_WIDTH] = {};
	POS tStartPos = {};
	POS tEndPos = {};

	PLAYER theif = {};
	PLAYER tagger = {};
	theif.playerRole = PLAYER_ROLE::THIEF;
	tagger.playerRole = PLAYER_ROLE::TAGGER;

	clock_t time = clock();

	theif.tPos.y = 9;
	theif.tPos.x = 1;

	tagger.tPos.y = 9;
	tagger.tPos.x = 33;

	Init(arrMap, &tStartPos, &tEndPos);
	if (!Title())
		return 0;
	else
	{
		while (true)
		{
			Gotoxy(0, 0);
			Render(arrMap, &theif, &tagger);
			if (!Update(arrMap, &theif, &tagger)) break;
			time = CreateItem(arrMap, time);
		}
	}
}