// staff_attendance.cpp: определяет точку входа для консольного приложения.
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

	// приветствие
	coutWelcome();
	_getch();

	// диалог с пользователем
	while (true)
	{
		system("cls");
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << ">Выберите, какой метод вы желаете использовать.\n";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		cout << "\n\t1. Групповая экспертная оценка";
		cout << "\n\t2. Обработка парных сравнений";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);


		_getch();
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "\n\n>--------------------------------------------------";
		cout << "\n\tДля выхода - нажмите ESC";
		cout << "\n\tДля нового расчёта - нажмите любую клавишу";

		char c;
		c = _getch();
		if (c == 27) break;
		else continue;
	}
	
	
	return 0;
}

