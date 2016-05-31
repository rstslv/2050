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

double score = 0; // ���� ������
double Max = 0; // ������� ������������ ������
int PosForX() // ���������� �� ������
{
	//srand(time(0));
	int x = rand() % 4; // �� 0 �� 3 ������������
	return x;
}
int PosForY() // ���������� �� ������
{
	//srand(time(0));
	int y = rand() % 4;
	return y;
}

int CurNumb() // ����������� �������� ������ (2 � ������������ 90%; 4 � ������������ 10%)
{
	//srand(time(0));
	int x(0);
	int y = rand() % 10;  // �� 0 �� 9 ������������
	if (y == 9)
		return x = 4;
	else
		return x = 2;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	int map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
	int h_map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }; // ��������������� �������
	int end_map[4][4] = { { 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }; //��� ���� ��������������� �������
	int i, j;
	int flag = 0; // ����� ���������� ��������� ����� ���� 
	string yn; // ����������, ���������� ��������� ������ ����� ���������� �������� ���� ���� (����� 2048 ����� �� ����� �� ������)
	srand(time(NULL));
	i = PosForX(); // �������� �������������� ���������� ��� ������ �����(1 ���)
	j = PosForY();
	system("cls");
	NewKl(map); //������� ����� �������� ������
	i = PosForX(); //(2 ���)
	j = PosForY();
	system("cls");
	NewKl(map);
	char key = 0;  // ���������� ������ ����
	while (true)
	{
		while (flag < 2)  // ���� ����� ����� ��������� � ���������� ��������� (1 ��� 2)
		{
			if (_kbhit())//���� ����� ���������� �� ������
			{
				CopyM(map, end_map);
				key = _getch();
				switch (key) // ����� ����������� ����(�� ��������)
				{
				case 72: // up
				{
					system("cls"); // ������� ������
					CopyM(map, h_map); // ��������� �������������� ������� ���������� ��������
					MUp(map); // ������ ���

					if (Change(map, h_map)) // ��������� ������� ��������� � ������� ����
					{
						NewKl(map);  // � ������ ������, ������� ����� �������� ������
						break;
					}
					else
					{
						PrintMap(map); // ����� ������������� ������ ����������� ������� ���������� ���
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
				default: // ����� ��������

					break;
				}
				if (IfFul(map) && Change(map, end_map)) {  // ��������� ���� �� ������ ���������� � ���������� ��������� ����� ����
					cout << "You lose";   // � ������ ������, ���� ��������
					flag = 2; // flag == 2 - ����� ��������� ����
				}
				if ((Max >= 2048) && (flag == 0)) // ����������  ��������� ���� ����, ���������� ������ ���� ��������� ����, ���� ���������� � �� ���������
				{
					system("cls");
					cout << "Congratulations! You Win!" << endl;
					cout << "Do you want to continue the game? (y/n)" << endl;
					yn = _getch();
					if (yn == "y") {
						flag = 1;   // flag == 1 - ��������� ���������� �������� ���� � ������������ ����������� ����
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



void PrintMap(int myMap[][4])  // �������, ������������ �� ������ ������� ���� � ������� ����� ������
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			if (myMap[i][j] == 0)
			{
				cout.width(3);  // ������ ��������������� �����
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
void NewKl(int(&myMap)[4][4]) // ������� �������� ����� �������� ������
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

void MLeft(int(&myMap)[4][4])   // ������� ���� ������ �����
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
		for (int j = 0;j<3;j++)   // ������ � ������� ���������� ��������� � ����, ������ ����� ������
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

void CopyM(int(&myMap1)[4][4], int(&myMap2)[4][4])  // ������� ����������� ������
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4;j++)
		{
			myMap2[i][j] = myMap1[i][j];
		}
	}
}
bool Change(int(&myMap1)[4][4], int(&myMap2)[4][4]) // �������� �� ��������� ������� ����� ��������� ����
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

bool IfFul(int(&myMap)[4][4]) // ������� �������� �� ������� �������
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
