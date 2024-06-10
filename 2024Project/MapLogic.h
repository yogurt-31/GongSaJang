#pragma once
const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 20;

typedef struct _targetpos
{
	int x;
	int y;
	bool operator ==(const _targetpos& _pos)
	{
		if (x == _pos.x && y == _pos.y)
			return true;
		else
			return false;
	}

}POSITION, * PPOSITION;

enum class OBJ_TYPE
{
	WALL = '0', ROAD, START, GOAL
};
#include<vector>
using std::vector;
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPOSITION _pStartPos, PPOSITION _pEndPos);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);