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

	theif.tPos = { 1,9 };

	tagger.tPos = { 33,9 };

	Init(arrMap, &tStartPos, &tEndPos);

	if (!Title())
		return 0;
	else
	{
		while (true)
		{
			Gotoxy(0, 0);
			Render(arrMap, &theif, &tagger);
			time = CreateItem(arrMap, time);
			if (!Update(arrMap, &theif, &tagger)) break;
		}
	}
}