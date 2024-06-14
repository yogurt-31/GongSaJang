#pragma once
#include "PlayerLogic.h"

const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 20;

enum class OBJ_TYPE
{
	WALL = '0', ROAD, START, GOAL
};

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPOS _pStartPos, PPOS _pEndPos);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);