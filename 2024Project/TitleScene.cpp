#include<iostream>
#include<fcntl.h>
#include<io.h>
#include<Windows.h>
#include "TitleScene.h"
#include "console.h"
using namespace std;

void TitleRender()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	
	SetColor((int)COLOR::SKYBLUE);
	wcout << L" ________  ___  ___  ________   ___            ________  ________  _________  ________  ___  ___  ___       " << endl;
	wcout << L"|\\   __  \\|\\  \\|\\  \\|\\   ___  \\|\\  \\          |\\   ____\\|\\   __  \\|\\___   ___\\\\   ____\\|\\  \\|\\  \\|\\  \\      " << endl;
	wcout << L"\\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\         \\ \\  \\___|\\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\     " << endl;
	wcout << L" \\ \\   _  _\\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\         \\ \\  \\    \\ \\   __  \\   \\ \\  \\ \\ \\  \\    \\ \\   __  \\ \\  \\    " << endl;
	wcout << L"  \\ \\  \\\\  \\\\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\__\\         \\ \\  \\____\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\____\\ \\  \\ \\  \\ \\__\\   " << endl;
	wcout << L"   \\ \\__\\\\ _\\\\ \\_______\\ \\__\\\\ \\__\\|__|          \\ \\_______\\ \\__\\ \\__\\   \\ \\__\\ \\ \\_______\\ \\__\\ \\__\\|__|   " << endl;
    wcout << L"    \\|__|\\|__|\\|_______|\\|__| \\|__|   ___         \\|_______|\\|__|\\|__|    \\|__|  \\|_______|\\|__|\\|__|   ___ " << endl;
	wcout << L"                                     |\\__\\                                                             |\\__\\"  << endl;
    wcout << L"                                     \\|__|                                                             \\|__|" << endl;
	SetColor((int)COLOR::WHITE);

	int curmode = _setmode(_fileno(stdout), prevmode);

}

bool Title()
{
	while (true)
	{
		TitleRender();
		MENU eMenu = MenuRender();
		switch (eMenu)
		{
		case MENU::START:
			EnterAnimation();
			// 애니메이션
			return true;
		case MENU::INFO:
			InfoRender();
			return false;
		case MENU::QUIT:
			return false;
		}
	}

}

MENU MenuRender()
{
	COORD Resolution = GetConsoleResolution();
	int x = Resolution.X / 2.5;
	int y = Resolution.Y / 2;
	int originy = y;
	Gotoxy(x, y);
	cout << "게임 시작";
	Gotoxy(x, y + 1);
	cout << "게임 정보";
	Gotoxy(x, y + 2);
	cout << "종료 하기";
	while (true)
	{
		KEY eKey = KeyController();
		switch (eKey)
		{
		case KEY::UP:
		{
			if (y > originy)
			{
				Gotoxy(x - 2, y);
				cout << " ";
				Gotoxy(x - 2, --y);
				SetColor((int)COLOR::LIGHT_YELLOW);
				cout << ">";
				SetColor((int)COLOR::WHITE);
				Sleep(100);
			}
		}
		break;
		case KEY::DOWN:
		{
			if (y < originy + 2)
			{
				Gotoxy(x - 2, y);
				cout << " ";
				Gotoxy(x - 2, ++y);
				SetColor((int)COLOR::LIGHT_YELLOW);
				cout << ">";
				SetColor((int)COLOR::WHITE);
				Sleep(100);
			}
		}
		break;
		case KEY::SPACE:
			if (originy == y)
				return MENU::START;
			else if (originy + 1 == y)
				return MENU::INFO;
			else if (originy + 2 == y)
				return MENU::QUIT;
		}
	}
}

void InfoRender()
{
	system("cls");

	SetColor((int)COLOR::SKYBLUE);
	cout << "[조작법]" << endl;
	SetColor((int)COLOR::WHITE);
	cout << "도망자 : WASD" << endl;
	cout << "술래 : 방향키" << endl;

	cout << endl;

	SetColor((int)COLOR::SKYBLUE);
	cout << "[게임 플레이 방법]" << endl;
	SetColor((int)COLOR::WHITE);
	cout << "도망자는 토큰을 모두 먹을 시 승리," << endl;
	cout << "술래는 도망자를 잡으면 승리합니다." << endl;

	cout << endl;
	SetColor((int)COLOR::LIGHT_RED);
	cout << "나가기 : 아래 방향키" << endl;
	SetColor((int)COLOR::WHITE);

	while (true)
	{
		if (KeyController() == KEY::DOWN)
		{
			system("cls");
			Title();
		}
	}
}

KEY KeyController()
{
	//_getch(); _kbhit(); 로 바꾸기.
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		//Sleep(100);
		return KEY::UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		return KEY::DOWN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		return KEY::SPACE;
	}
	//Sleep(100);
	return KEY::FAIL;
}

void EnterAnimation()
{
	COORD Resolution = GetConsoleResolution();
	int width = Resolution.X;
	int height = Resolution.Y;
	int animtime = 20;

	SetColor((int)COLOR::SKYBLUE);
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width  /2; j++)
		{
			Gotoxy(j * 2, i);
			cout << "  ";
		}
		Sleep(animtime);
	}
	SetColor((int)COLOR::WHITE);
	system("cls");
}
