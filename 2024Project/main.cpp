#include<Windows.h>
#include<fstream>
#include<string>

#include "console.h"
#include "TitleScene.h"
#include "GameLogic.h"
#include "MapLogic.h"

int main()
{
	while (true) {
		char arrMap[MAP_HEIGHT][MAP_WIDTH] = {};

		PLAYER theif = {};
		theif.tPos = { 1,9 };
		theif.playerRole = PLAYER_ROLE::THIEF;

		PLAYER tagger = {};
		tagger.tPos = { 33,9 };
		tagger.playerRole = PLAYER_ROLE::TAGGER;

		Init(arrMap);

		std::string winnerText;

		if (!Title())
			return 0;
		else
		{
			clock_t time = clock();
			while (true)
			{
				Gotoxy(0, 0);
				Render(arrMap, &theif, &tagger);
				time = CreateItem(arrMap, time);
				winnerText = Update(arrMap, &theif, &tagger);

				if (winnerText != "") break;
			}
			system("cls");
			cout << winnerText << endl;
			system("pause");
		}
	}
}