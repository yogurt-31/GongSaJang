#include "GameOver.h"
#include <Windows.h>

void GameOver(std::string description)
{
	system("cls");
	std::cout << description;
}
