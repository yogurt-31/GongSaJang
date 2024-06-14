#pragma once
#include "Logic.h"
#include "PlayerLogic.h"

enum class OBJ_TYPE
{
	WALL = '0', BEAN, ROAD
};

void DelayTime();
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPOS _pStartPos, PPOS _pEndPos);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _thief, PPLAYER _tagger);