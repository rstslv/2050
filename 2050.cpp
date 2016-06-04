#include "stdafx.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<conio.h>


using namespace std;

void PrintMap(int myMap[][4]);
void MRight(int(&myMap)[4][4]);
void MLeft(int(&myMap)[4][4]);
void MUp(int(&myMap)[4][4]);
void MDown(int(&myMap)[4][4]);
void NewKl(int(&myMap)[4][4]);
void CopyM(int(&myMap1)[4][4], int(&myMap2)[4][4]);
bool Change(int(&myMap1)[4][4], int(&myMap2)[4][4]);
bool IfFul(int(&myMap)[4][4]);

double score = 0; // счет игрока
double Max = 0; // номинал максимальной плитки
int PosForX() // координата по ширине
{
	//srand(time(0));
	int x = rand() % 4; // от 0 до 3 включительно
	return x;
}
int PosForY() // координата по высоте
{
	//srand(time(0));
	int y = rand() % 4;
	return y;
}

int CurNumb() // определение номинала плитки (2 с вероятностью 90%; 4 с вероятностью 10%)
{
	//srand(time(0));
	int x(0);
	int y = rand() % 10;  // от 0 до 9 включительно
	if (y == 9)
		return x = 4;
	else
		return x = 2;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	int map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
	int h_map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }; // вспомогательная матрица
	int end_map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }; //еще одна вспомогательная матрица
	int flag = 0; // метка завершения основного цикла игры 
	string yn; // переменная, выясняющая намерения игрока после достижения основной цели игры (набор 2048 очков на любой из плиток)
	srand(time(NULL));
	system("cls");
	NewKl(map); //создаем новую непустую плитку (2 раза)
	system("cls");
	NewKl(map);
	char key = 0;  // переменная выбора хода
	while (true)
	{
		while (flag < 2)  // пока метка флага находится в допустимых состояних (1 или 2)
		{
			if (_kbhit())//если буфер клавиатуры не пустой
			{
				CopyM(map, end_map);
				key = _getch();
				switch (key) // выбор направления хода(по стрелкам)
				{
				case 72: // up
				{
					system("cls"); // очистка экрана
					CopyM(map, h_map); // заполняем дополнительную матрицу значениями основной
					MUp(map); // делаем ход

					if (Change(map, h_map)) // проверяем наличие изменения в игровом поле
					{
						NewKl(map);  // в случае успеха, создаем новую непустую клетку
						break;
					}
					else
					{
						PrintMap(map); // иначе предоставляем игроку возможность сделать допустимый ход
						break;
					}
				}
				case 75: // left
				{
					system("cls");
					CopyM(map, h_map);
					MLeft(map);

					if (Change(map, h_map))
					{
						NewKl(map);
						break;
					}
					else
					{
						PrintMap(map);
						break;
					}
				}
				case 77: // right
				{
					system("cls");
					CopyM(map, h_map);
					MRight(map);
					if (Change(map, h_map))
					{
						NewKl(map);
						break;
					}
					else
					{
						PrintMap(map);
						break;
					}
				}
				case 80: // down
				{
					system("cls");
					CopyM(map, h_map);
					MDown(map);

					if (Change(map, h_map))
					{
						NewKl(map);
						break;
					}
					else
					{
						PrintMap(map);
						break;
					}
				}
				default: // ветвь проверки

					break;
				}
				if (IfFul(map) && Change(map, end_map)) {  // проверяем поле на полное заполнение и отсутствие изменений после хода
					cout << "Wasted";   // в случае успеха, игра окончена
					flag = 2; // flag == 2 - метка окончания игры
				}
				if ((Max >= 2048) && (flag == 0)) // достижение  основоной цели игры, предлагаем игроку либо закончить игру, либо продолжить её до проигрыша
				{
					system("cls");
					cout << "Congratulations! You Win!" << endl;
					cout << "Do you want to continue the game? (y/n)" << endl;
					yn = _getch();
					if (yn == "y") {
						flag = 1;   // flag == 1 - состояние достижения основной цели и последующего продолжения игры
					}
					if (yn == "n") {
						flag = 2;
					}
				} break;
				if ((Max >= 2048) && (flag == 1))
				{
					break;
				}
			}
		}
	}
}



void PrintMap(int myMap[][4])  // функция, изображающая на экране игровое поле и значени счета игрока
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			if (myMap[i][j] == 0)
			{
				cout.width(3);  // задаем форматированный вывод
				cout << "-" << " ";

			}
			else
			{
				cout.width(3);
				cout << myMap[i][j] << " ";

			}
		}
		cout << endl;
		cout << endl;
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
}
void NewKl(int(&myMap)[4][4]) // функция создания новой непустой плитки
{
	int i(0), j(0);
	while (true)
	{
		i = PosForX();
		j = PosForY();
		if (myMap[i][j] == 0)
		{
			myMap[i][j] = CurNumb();
			break;
		}
	}
	PrintMap(myMap);
}

void MLeft(int(&myMap)[4][4])   // функция хода игрока влево
{
	for (int i = 0;i<4;i++)
		for (int j = 0;j<4;j++)
		{
			if (myMap[i][j] == 0)
			{
				for (int k = j + 1;k<4;k++)
					if (myMap[i][k])
					{
						myMap[i][j] = myMap[i][k];
						myMap[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0;i<4;i++)
		for (int j = 0;j<3;j++)   // клетки с равными номиналами соединяем в одно, другую делая пустой
		{
			if (myMap[i][j] && myMap[i][j] == myMap[i][j + 1])
			{
				myMap[i][j] += myMap[i][j + 1];
				myMap[i][j + 1] = 0;
				score += (((log2(myMap[i][j])) - 1)*myMap[i][j]);
				if (myMap[i][j] > Max)
					Max = myMap[i][j];
			}
		}
}
void MUp(int(&myMap)[4][4])
{
	for (int i = 0;i<4;i++)
		for (int j = 0;j<4;j++)
		{
			if (myMap[j][i] == 0)
			{
				for (int k = j + 1;k<4;k++)
					if (myMap[k][i])
					{
						myMap[j][i] = myMap[k][i];
						myMap[k][i] = 0;
						break;
					}
			}

		}
	for (int i = 0;i<4;i++)
		for (int j = 0;j<3;j++)
		{
			if (myMap[j][i] && myMap[j][i] == myMap[j + 1][i])
			{
				myMap[j][i] += myMap[j + 1][i];
				myMap[j + 1][i] = 0;
				score += (((log2(myMap[j][i])) - 1)*myMap[j][i]);
				if (myMap[i][j] > Max)
					Max = myMap[i][j];
			}
		}
}
void MDown(int(&myMap)[4][4])
{
	for (int i = 0;i<4;i++)
		for (int j = 3;j >= 0;j--)
		{
			if (myMap[j][i] == 0)
			{
				for (int k = j - 1;k >= 0;k--)
					if (myMap[k][i])
					{
						myMap[j][i] = myMap[k][i];
						myMap[k][i] = 0;
						break;
					}
			}

		}
	for (int i = 0;i<4;i++)
		for (int j = 3;j>0;j--)
		{
			if (myMap[j][i] && myMap[j][i] == myMap[j - 1][i])
			{
				myMap[j][i] += myMap[j - 1][i];
				myMap[j - 1][i] = 0;
				score += (((log2(myMap[j][i])) - 1)*myMap[j][i]);
				if (myMap[i][j] > Max)
					Max = myMap[i][j];
			}
		}
}
void MRight(int(&myMap)[4][4])
{
	for (int i = 0;i<4;i++)
		for (int j = 3;j >= 0;j--)
		{
			if (myMap[i][j] == 0)
			{
				for (int k = j - 1;k >= 0;k--)
					if (myMap[i][k])
					{
						myMap[i][j] = myMap[i][k];
						myMap[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0;i<4;i++)
		for (int j = 3;j>0;j--)
		{
			if (myMap[i][j] && myMap[i][j] == myMap[i][j - 1])
			{
				myMap[i][j] += myMap[i][j - 1];
				myMap[i][j - 1] = 0;
				score += (((log2(myMap[i][j])) - 1)*myMap[i][j]);
				if (myMap[i][j] > Max)
					Max = myMap[i][j];
			}
		}
}

void CopyM(int(&myMap1)[4][4], int(&myMap2)[4][4])  // функция копированяи матриц
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			myMap2[i][j] = myMap1[i][j];
		}
	}
}
bool Change(int(&myMap1)[4][4], int(&myMap2)[4][4]) // проверка на изменения матрицы после очереного хода
{
	int err = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			if (myMap1[i][j] != myMap2[i][j])
				err += 1;
		}
	}
	if (err > 0)
		return 1;
	else
		return 0;
}

bool IfFul(int(&myMap)[4][4]) // функция проверки но полноту матрицы
{
	int ful = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			if (myMap[i][j] == 0)
				ful += 1;
		}
	}
	if (ful == 0)
		return 1;
	else
		return 0;
}
