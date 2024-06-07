#pragma once
void FullScreen();
void Gotoxy(int _x, int _y);
BOOL GotoPos(int _x, int _y);
COORD CursorPos();
void CursorVis(bool _vis, DWORD _size);
void SetColor(int _textcolor = 15, int _bgcolor = 0);
int GetColor();
void LockResize();
COORD GetConsoleResolution();
void SetFontSize(UINT _weight, UINT _fontx, UINT _fonty);
enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLOW, WHITE, END
};
#include<iostream>
using std::cout;
using std::wcout;
using std::endl;