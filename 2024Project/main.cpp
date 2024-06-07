#include<Windows.h>
#include "console.h"
#include "TitleScene.h"
#include<fstream>
#include<string>
int main()
{
	system("title 22Bombman | mode con cols=80 lines=40");
	CursorVis(false, 1);
	LockResize();
	SetFontSize(FW_BOLD, 20, 20);
	if (!Title())
		return 0;
	else
	{
		while (true)
		{
			Gotoxy(0, 0);
		}
	}
}