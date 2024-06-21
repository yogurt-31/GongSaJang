#pragma once
void TitleRender();
bool Title();
enum class MENU
{
	START, INFO, QUIT
};
MENU MenuRender();
void InfoRender();
enum class KEY
{
	UP, DOWN, SPACE, FAIL
};
KEY KeyController();
void EnterAnimation();
void FlickerAnimation(int x,int y);
void ChangeTitleColor();