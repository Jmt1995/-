#include "Snake.h"
#include<Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
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
// �������еĽڵ� 
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


	//����ǽ��
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
// ɾ��β���ڵ�
void Snake::delPoint()
{
	Point* pCur = pHead;
	Point* pBef = pHead;

	if (pHead == NULL || pHead->next == NULL)
	{
		cout << "�ڵ�����2 �޷�ɾ��" << endl;
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
		cout << "�Ƿ��ַ�" << endl;
		break;
	}

	//�ж��Ƿ�ɹ�
	if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
	{
		gotoxy(11*2, 13);
		cout << "GAME OVER!" << endl;
		gotoxy(11 * 2, 14);
		cout << "�ܷ���:" << getScore()<< endl;
		return false;
	}

	//�ɹ�  �Ե�ʳ��  û�гԵ�
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
