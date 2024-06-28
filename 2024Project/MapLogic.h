#pragma once
#include "GameLogic.h"

enum class OBJ_TYPE
{
	WALL = '0', BEAN, ROAD, ITEM_CHANGE
};

void DelayTime(int time);
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER thief, PPLAYER tagger);
int BeanCount(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);