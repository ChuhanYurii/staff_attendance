// staff_attendance.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include "globalUtils.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	system("color F1");
	system("cls");

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	double ** mark = 0;

	// �����������
	coutWelcome();
	_getch();

	// ������ � �������������
	while (true)
	{
		system("cls");
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << ">��������, ����� ����� �� ������� ������������.\n";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		cout << "\n\t1. ��������� ���������� ������";
		cout << "\n\t2. ��������� ������ ���������";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);


		_getch();
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "\n\n>--------------------------------------------------";
		cout << "\n\t��� ������ - ������� ESC";
		cout << "\n\t��� ������ ������� - ������� ����� �������";

		char c;
		c = _getch();
		if (c == 27) break;
		else continue;
	}
	
	
	return 0;
}

