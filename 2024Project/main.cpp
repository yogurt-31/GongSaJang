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

	theif.tPos.y = 5;
	theif.tPos.x = 5;

	tagger.tPos.y = 15;
	tagger.tPos.x = 15;

	Init(arrMap, &tStartPos, &tEndPos);
	if (!Title())
		return 0;
	else
	{
		while (true)
		{
			Gotoxy(0, 0);
			Render(arrMap, &theif, &tagger);
			Update(arrMap, &theif, &tagger);
		}
	}
}