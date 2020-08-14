#pragma once
#include "wall.h"
#include "Food.h"
#include<Windows.h>
class Snake
{
	struct Point
	{
		int x;
		int y;
		Point* next;
	};
private:
	Wall& wall;
	Food& food;
	Point* pHead;
	int score;


public:
	
	Snake(Wall &tempWall, Food& tempFood);
	enum {
		UP = 'w',
		DOWN = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};
	void addScore();
	int getScore();

	void initSnake();

	void destroyPoint();

	void addPoint(int x, int y);
	void delPoint();
	bool move( char key);
};

