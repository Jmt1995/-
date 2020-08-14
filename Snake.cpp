#include "Snake.h"
#include<Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}


Snake::Snake(Wall& tempWall, Food& tempFood): wall(tempWall), food(tempFood)
{
	pHead = NULL;
}
void Snake::addScore()
{
	score++;
}
int Snake::getScore()
{
	return score;
}
void Snake::initSnake()
{
	score = 0;
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}
// 销毁所有的节点 
void Snake::destroyPoint()
{
	Point* pCur = pHead;
	while (pHead != nullptr)
	{
		pHead = pHead->next;
		delete pCur;
		pCur = pHead;
	}

}

void Snake::addPoint(int x, int y)
{
	Point* newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = nullptr;


	//设置墙上
	if (pHead != nullptr)
	{
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(pHead->y * 2, pHead->x);
		cout << "=";
	}
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(pHead->y * 2, pHead->x);
	cout << "@";

//	gotoxy(13*2, 13 * 2);

}
// 删除尾部节点
void Snake::delPoint()
{
	Point* pCur = pHead;
	Point* pBef = pHead;

	if (pHead == NULL || pHead->next == NULL)
	{
		cout << "节点少于2 无法删除" << endl;
		return;
	}

	while (pCur->next != NULL)
	{
		pBef = pCur;
		pCur = pCur->next;
	}
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy(pCur->y * 2, pCur->x);
	cout << " ";


	pBef->next = NULL;
	delete pCur;
	pCur = NULL;
}

bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;
	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		cout << "非法字符" << endl;
		break;
	}

	//判断是否成功
	if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
	{
		gotoxy(11*2, 13);
		cout << "GAME OVER!" << endl;
		gotoxy(11 * 2, 14);
		cout << "总分数:" << getScore()<< endl;
		return false;
	}

	//成功  吃到食物  没有吃到
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		food.setFood();
		
		addScore();
		gotoxy(5, 26);
		cout << getScore() ;
		
	}
	else
	{
		addPoint(x, y);
		delPoint();
	}
	return true;
}
