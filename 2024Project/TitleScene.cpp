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
	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗" << endl;
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗████╗ ████║██╔══██╗████╗  ██║" << endl;
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝██╔████╔██║███████║██╔██╗ ██║" << endl;
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║" << endl;
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║" << endl;
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝" << endl;
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
			break;
		case MENU::QUIT:
			return false;
		}
	}

}

MENU MenuRender()
{
	COORD Resolution = GetConsoleResolution();
	int x = Resolution.X / 3;
	int y = Resolution.Y / 2.5;
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
				cout << ">";
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
				cout << ">";
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
	cout << "[조작법]" << endl;
	cout << "[게임 플레이 방법]" << endl;
	while (true)
	{
		if (KeyController() == KEY::SPACE)
			break;
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

	// 5번 깜빡거리기.
	for (int i = 0; i < 5; ++i)
	{
		Gotoxy(0, 0);
		SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
		system("cls");
		/*for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width / 2; ++k)
			{
				cout << "  ";
			}
			cout << endl;
		}*/
		Sleep(animtime);

		Gotoxy(0, 0);
		SetColor((int)COLOR::WHITE);
		system("cls");
		/*	for (int j = 0; j < height; j++)
			{
				for (int k = 0; k < width / 2; ++k)
				{
					cout << "  ";
				}
				cout << endl;
			}*/
		Sleep(animtime);
	}

	// 크로스.
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	for (int i = 0; i < width / 2; ++i)
	{
		for (int j = 0; j < height; j += 2)
		{
			Gotoxy(i * 2, j);
			cout << "  ";
		}
		for (int j = 1; j < height; j += 2)
		{
			Gotoxy(width - 2 - i * 2, j);
			cout << "  ";
		}
		Sleep(animtime);
	}
	SetColor((int)COLOR::WHITE);
	system("cls");
	//SetColor((int)COLOR::WHITE, (int)COLOR::MINT);
	//system("cls");
}
