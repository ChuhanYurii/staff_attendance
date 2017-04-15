// staff_attendance.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "globalUtils.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	system("color F1");
	system("cls");

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	vector <Staff*> StaffInfo;

	// приветствие
	coutWelcome();
	_getch();

	// диалог с пользователем
	while (true)
	{
		system("cls");
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << ">Выберите необходимое действие.\n";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		cout << "\n\t1. Просмотр списка сотрудников";
		cout << "\n\t2. Фиксация времени прихода и ухода с работы";
		cout << "\n\t3. Общая информация о каждом работнике ";
		cout << "\n\t4. Добавление работника ";
		cout << "\n\t5. Редактирование информации о работнике ";
		cout << "\n\t6. Удаление работника ";
		cout << "\n\t7. Сортировка списка работников по имени ";
		cout << "\n\t7. Поиск работника по имени ";
		cout << "\n\t8. Рейтинг работников";
		cout << "\n\t9. Посчитать зарплату";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				
		int downloadMode = getMode(9);
		string tempStr = "";
		
		read_file("staff.txt", StaffInfo);
		
		switch (downloadMode)
		{
		case 1: // Просмотр списка сотрудников
			ShowStaffList(StaffInfo);
			break;

		case 4:
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите ФИО нового работника ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);
			StaffInfo.push_back(new Staff());
			StaffInfo[StaffInfo.size() - 1]->setID(StaffInfo.size());
			StaffInfo[StaffInfo.size() - 1]->setName(tempStr);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Новый работник добавлен ";
			break;
		 
		default:
			break;
		}

		write_file("staff.txt", StaffInfo);

		_getch();
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "\n\n>--------------------------------------------------";
		cout << "\n\tДля выхода - нажмите ESC";
		cout << "\n\tДля нового действия - нажмите любую клавишу";

		char c;
		c = _getch();
		if (c == 27) break;
		else continue;
	}
	
	
	return 0;
}

