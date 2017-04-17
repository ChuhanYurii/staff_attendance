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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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
		cout << "\n\t8. Поиск работника по имени ";
		cout << "\n\t9. Рейтинг работников";
		cout << "\n\t10. Посчитать зарплату";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				
		int downloadMode = getMode(9);
		
		string tempStr = "";
		int idStaff = 1;
		
		read_file("staff.txt", StaffInfo);
		
		switch (downloadMode)
		{
		case 1: // Просмотр списка сотрудников
			ShowStaffList(StaffInfo);
			break;

		case 2: //Фиксация времени прихода и ухода с работы
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите номер работника, время которого необходимо зафиксировать ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Работника с таким номером нет";
				break;
			}
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите дату в формате дд.мм.гггг ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setDate(tempStr);

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << " Введите время прихода на работу в формате чч.мм ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setTimeBegin(tempStr);

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << " Введите время ухода с работы в формате чч.мм ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setTimeEnd(tempStr);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Время зафиксировано ";
			break;

		case 4: //Добавление работника
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

		case 5: //Редактирование информации о работнике
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите номер работника, ФИО которого необходимо редактировать ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Работника с таким номером нет";
				break;
			}
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите новое ФИО работника ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);
			
			StaffInfo[idStaff - 1]->setName(tempStr);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n ФИО изменено ";
			break;
		
		case 6: //Удаление работника 
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Введите номер работника, которого необходимо удалить ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Работника с таким номером нет";
				break;
			}

			StaffInfo.erase(StaffInfo.begin() + idStaff - 1);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Работник удалён";
			break;

		case 7: //Сортировка списка работников по имени
			ShowStaffList(StaffInfo);
			
			struct sort_class
			{
				bool operator() (Staff* i, Staff* j)
				{
					return (i->getName() < j->getName());
				}
			} sort_object;

			sort(StaffInfo.begin(), StaffInfo.end(), sort_object);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n После сортировки";
			ShowStaffList(StaffInfo);
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