#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "wall.h"
#include "Snake.h"
#include "Food.h"
#include <ctime>
#include <conio.h>
#include<Windows.h>
using namespace std;
/***
墙


**/
void gotoxy3(int x, int y) {
    COORD pos = { x,y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
void HideCursor() //隐藏光标 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

int main()
{
    //随机种子
    srand((unsigned int) time(NULL));
    bool isDead = false;
    char preKey = NULL;
   // cout << "Hello World!\n";
    Wall w;
    w.initWall();
    w.printWall();
    cout << "分数:0" << endl;

    Food food(w);
    food.setFood();

    Snake snake(w, food);
    snake.initSnake();


    
    
   // gotoxy(5*2, 5);
    while (!isDead)
    {
        char key = _getch();
        if (preKey == NULL && key == snake.LEFT)
        {
            continue;
        }
        do {
            HideCursor();
            //是否是合法键
            if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
            {

                if ((key == snake.LEFT && preKey == snake.RIGHT) || 
                    (key == snake.RIGHT && preKey == snake.LEFT) || 
                    (key == snake.UP && preKey == snake.DOWN) || 
                    (key == snake.DOWN && preKey == snake.UP))
                {
                    key = preKey;
                }
                else
                {
                    preKey = key;
                }
                if (snake.move(key))
                {
                    
                 //   gotoxy3(6, 26);
                  //  cout << snake.getScore;


                  //  system("cls");
                  //  w.printWall();
                  //  gotoxy(0, 0);
                    Sleep(500);
                }
                else
                {
                    isDead = true;
                    break;
                }
            }
            else
            {
                key = preKey;
            }
        } while (!_kbhit());//当没有键盘输入的时候返回0

        if (isDead)
        {
           // w.printWall();
            //system("cls");
            gotoxy3(0, 27);
            cout << "按下R重新开始游戏" << endl;
            char recov = _getch();
            system("cls");
            if (recov == 'r')
            {
                //gotoxy3(0, 0);
                w.initWall();
                w.printWall();
                cout << "分数:" << endl;
                food.setFood();
                snake.initSnake();
                
               // w.printWall();
                preKey = NULL;
                isDead = false;
            }
                

        }

    }

    

    return EXIT_SUCCESS;
}
