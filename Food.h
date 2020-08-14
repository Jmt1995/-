#pragma once
#include "wall.h"
#include <Windows.h>
class Food
{
private:
	int foodX;
	int foodY;
	Wall& wall;
public:
	Food(Wall& tempWall);
	void setFood();

};


