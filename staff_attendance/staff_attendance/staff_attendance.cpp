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
	//setlocale(LC_ALL, "rus");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);

	system("color F1");
	system("cls");

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	vector <Staff*> StaffInfo, tempStaffInfo;

	// приветствие
	coutWelcome();
	_getch();

	// диалог с пользователем
	while (true)
	{
		system("cls");
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << ">vyberte pozadovanou akce.\n";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		cout << "\n\t1. seznam zamestnacu";
		cout << "\n\t2. zadat prichod do zamestnani a odchod ze zamestnani";
		cout << "\n\t3. souhrna informace o jednotlivych zamestnancich ";
		cout << "\n\t4. vkladani zamestnancu ";
		cout << "\n\t5. upravovani informace o zamestnance";
		cout << "\n\t6. odebirani zamestnancu  ";
		cout << "\n\t7. razeni podle jmena";
		cout << "\n\t8. vyhledavani podle jmena ";
		cout << "\n\t9. zebricek zamestnancu podle odpracova doby";
		cout << "\n\t10. vypocitat mzdu za zvolene obdobi ";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				
		int downloadMode = getMode(10);
		
		string tempStr = "";
		int idStaff = 1, month = 1;
		double salary = 0., _worktime = 0.;
		COORD position;
		
		read_file("staff.txt", StaffInfo);
		
		switch (downloadMode)
		{
		case 1: // Просмотр списка сотрудников
			ShowStaffList(StaffInfo);
			break;

		case 2: //Фиксация времени прихода и ухода с работы
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n zvolte cislo a cas zamestnance ktereho chcete evidovat ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Pracovnik z takovymhle cislem neexistuje";
				break;
			}
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n napiste datum ve formatu dd.cc.rrrr ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setDate(tempStr);

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << " napiste cas prechodu do zamestnani ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setTimeBegin(tempStr);

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << " napiste cas odchosu ze zamestnani  ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);			
			StaffInfo[idStaff - 1]->setTimeEnd(tempStr);

			StaffInfo[idStaff - 1]->setWorkTime();
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n cas je stanoveny ";
			break;

		case 3: // Общая информация о каждом работнике
			ShowStaffInfoList(StaffInfo);
			break;

		case 4: //Добавление работника
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Napiste Jmeno a Prijmeni noveho zamestnance  ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);
			StaffInfo.push_back(new Staff());
			StaffInfo[StaffInfo.size() - 1]->setID(StaffInfo.size());
			StaffInfo[StaffInfo.size() - 1]->setName(tempStr);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Novy zamestnanec dodan ";
			break;

		case 5: //Редактирование информации о работнике
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Napiste cislo zamestnance, ktereho chcete upravit ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Pracovnik z takovymhle cislem neexistuje";
				break;
			}
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Napiste nove Jmeno a Prijmeni zamestance ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);
			
			StaffInfo[idStaff - 1]->setName(tempStr);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Jmeno a Prijmeni bylo zmeneno ";
			break;
		
		case 6: //Удаление работника 
			ShowStaffList(StaffInfo);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Napiste cislo zamestnance ktereho chcete odebrat ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			idStaff = getNumber();

			if (idStaff > StaffInfo.size()) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Pracovnik z takovymhle cislem neexistuje";
				break;
			}

			StaffInfo.erase(StaffInfo.begin() + idStaff - 1);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n Zamestnanec byl odebran ";
			break;

		case 7: //Сортировка списка работников по имени
			ShowStaffList(StaffInfo);
			
			struct sort_class2
			{
				bool operator() (Staff* i, Staff* j)
				{
					return (i->getName() < j->getName());
				}
			} sort_object2;

			sort(StaffInfo.begin(), StaffInfo.end(), sort_object2);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n po razeni podle jmena";
			ShowStaffList(StaffInfo);
			break;


		case 8: //Поиск работника по имени
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n vyhledavani zamestnancu ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);

			if (!(FindStaff(StaffInfo, tempStr))) {
				SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				cout << "\n Neexistuje zamestnance z takovymhle jmenem";
			}

			break;

		case 9: //Рейтинг работников
			tempStaffInfo = StaffInfo;

			struct sort_class
			{
				bool operator() (Staff* i, Staff* j)
				{
					return (i->getAllWorkTime() > j->getAllWorkTime());
				}
			} sort_object;

			sort(tempStaffInfo.begin(), tempStaffInfo.end(), sort_object);
			
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\nzebricek zamestnancu podle odpracovane doby ";
			cout << "\n\nCislo     Jmeno a Prijmeni           Pocet hodin";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			for (size_t i = 0, y = 17; i < StaffInfo.size(); ++i,++y)
			{
				tempStaffInfo[i]->setID(i + 1);
				cout << "\n" << setw(3) << tempStaffInfo[i]->getID() << ". ";
				++y;
				cout << tempStaffInfo[i]->getName().c_str();
				position.X = 33;
				position.Y = y;
				SetConsoleCursorPosition(hStdout, position);
				cout << setw(11) << setprecision(2) << fixed << tempStaffInfo[i]->getAllWorkTime();
				cout << endl;
			}

			break;

		case 10: //Посчитать зарплату
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\nnapiste cislo mesice (ve formate dve cislice) za ktery byla vypoctana mzda==>";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n zadejte hodinovu sazbu ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			salary = getDouble();

			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\nCislo     Jmeno a Prijmeni        sazba za " << tempStr.c_str() << " mesic";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);

			for (size_t i = 0, y = 19; i < StaffInfo.size(); ++i,++y)
			{
				_worktime = 0.;
				for (size_t j = 0; j < StaffInfo[i]->getDate().size(); ++j)
				{
					if (StaffInfo[i]->getDate()[j].substr(3,2) == tempStr) _worktime += StaffInfo[i]->getWorkTime()[j];
				}
								
				cout << "\n" << setw(3) << StaffInfo[i]->getID() << ". ";
				++y;
				cout << StaffInfo[i]->getName().c_str();
				position.X = 33;
				position.Y = y;
				SetConsoleCursorPosition(hStdout, position);
				cout << setw(13) << setprecision(2) << fixed << _worktime * salary;
				cout << endl;
			}

			break;
		 
		default:
			break;
		}

		write_file("staff.txt", StaffInfo);

		_getch();
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "\n\n>--------------------------------------------------";
		cout << "\n\tpro ukonceni stisknete ESC";
		cout << "\n\taby zacat novou akci stisknete libovolnou klavesnici";

		char c;
		c = _getch();
		if (c == 27) break;
		else continue;
	}
	
	
	return 0;
}