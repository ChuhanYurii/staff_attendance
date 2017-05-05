#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "ClassStaff.h"

using namespace std;

// приветствие
void coutWelcome()
{
	cout << "\n\n\n\n\n\t\t\tZapoctovy program c.21\n";
	cout << "\t\t\tEvidence dochazky";
	cout << "\n\n\n\n\naby zacat, stiscnete libovolnou klavesnici . . .";
}

// установить цвет шрифта в консоле
void SetConsoleTextColor(HANDLE hStdout, int color)
{
	SetConsoleTextAttribute(hStdout, color |
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

// вспомогательная функция для ограничения ввода (только цифры)
bool test(char ch, const char *keys, unsigned int size)
{
	for (size_t i = 0; i<size; i++)
	if (keys[i] == ch) return true;
	return false;
}

// ввод только цифр
int getNumber()
{
	char numbers[11] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-' };
	string n;
	char ch;

	while ((ch = _getch()) != '\r')//enter
	if (test(ch, numbers, 11))
	{
		n += ch;
		cout << ch;
	}

	cout << endl;
	return atoi(n.c_str());
}

double getDouble()
{
	char numbers[12] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', ',' };
	string n;
	char ch;

	while ((ch = _getch()) != '\r')//enter
	if (test(ch, numbers, 12))
	{
		n += ch;
		cout << ch;
	}

	cout << endl;
	//return strtod(n.c_str(), end_ptr);
	const char* str = n.c_str();
	double res = atof(str);
	return res;
}


// выбор пункта меню
int getMode(unsigned int countMode)
{
	unsigned int mode = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << "\n\n zadejte cislo ==> ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		mode = getNumber();

		if ((mode > countMode) || (mode == 0))
		{
			SetConsoleTextColor(hStdout, FOREGROUND_RED);
			cout << "zvolena hodnota neodpovida seznamu !";
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		}
		else break;
	}

	return mode;
}

// чтение из файла
int read_file(char *fileName, vector <Staff*> &StaffInfo)
{		
	ifstream file;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	string tempStr;
	bool isWorkTime = false;
	int countStaff = 0;

	file.open(fileName, ios::in);
	if (!file.is_open()) // если файл не открыт
	{
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "File can not open!\n"; // сообщить об этом
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		return 0;
	}
	else
	{
		StaffInfo.clear();

		while (!file.eof()) //считывание с файла
		{
			getline(file, tempStr);
			
			if (tempStr == "staff") {
				StaffInfo.push_back(new Staff());
				countStaff++;
				StaffInfo[StaffInfo.size() - 1]->setID(countStaff);
				isWorkTime = false;
				continue;
			}
			
			if (tempStr == "worktime") {
				isWorkTime = true;
				continue;
			}
			
			if (tempStr == "endstaff") {
				StaffInfo[StaffInfo.size() - 1]->setWorkTime();
				continue;
			}
			
			if (isWorkTime){
				if (tempStr.find("date:") != -1) {
					tempStr = tempStr.substr(6);
					StaffInfo[StaffInfo.size() - 1]->setDate(tempStr);
				}
				if (tempStr.find("timebegin:") != -1) {
					tempStr = tempStr.substr(11);
					StaffInfo[StaffInfo.size() - 1]->setTimeBegin(tempStr);
				}
				if (tempStr.find("timeend:") != -1) {
					tempStr = tempStr.substr(9);
					StaffInfo[StaffInfo.size() - 1]->setTimeEnd(tempStr);
				}
			}
			else {
				StaffInfo[StaffInfo.size() - 1]->setName(tempStr);
			}
			
		}
	}
	file.close();

	return 1;
}

//запись в файл
void write_file(char *fileName, vector <Staff*> &StaffInfo)
{
	fstream file;      
	file.open(fileName, ios::out);
	
	for (unsigned int i = 0; i < StaffInfo.size(); ++i)
	{
		if (i != 0) file << endl;
		file << "staff" << endl;
		file << StaffInfo[i]->getName() << endl;
		for (unsigned int j = 0; j < StaffInfo[i]->getDate().size(); ++j)
		{
			file << "worktime" << endl;
			file << "date: " << StaffInfo[i]->getDate()[j] << endl;
			file << "timebegin: " << StaffInfo[i]->getTimeBegin()[j] << endl;
			file << "timeend: " << StaffInfo[i]->getTimeEnd()[j] << endl;
		}
		file << "endstaff";
	}

	file.close();
}

void ShowStaffList(vector <Staff*> &StaffInfo)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nseznam zamestnancu\n";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	for (unsigned int i = 0; i < StaffInfo.size(); ++i)
	{
		StaffInfo[i]->setID(i + 1);
		cout << "\t" << StaffInfo[i]->getID() << ". " << StaffInfo[i]->getName().c_str() << endl;
	}
}

void ShowStaffInfoList(vector <Staff*> &StaffInfo)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nsouhrna informace o jednotlivych zamestnancich\n";
	cout << "\nCislo       Jmeno a Prijmeni          Datum     Prichod    Odchod   Pocet hodin";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	for (size_t i = 0, y = 17; i < StaffInfo.size(); ++i,++y)
	{
		StaffInfo[i]->setID(i + 1);
		cout << "\n" << setw(3) << StaffInfo[i]->getID() << ". ";
		++y;
		cout << StaffInfo[i]->getName().c_str();
		for (size_t j = 0; j < StaffInfo[i]->getDate().size(); ++j)
		{
			position.X = 33;
			position.Y = y;
			SetConsoleCursorPosition(hStdout, position);
			cout << setw(12) << StaffInfo[i]->getDate()[j].c_str();
			cout << setw(9) << StaffInfo[i]->getTimeBegin()[j].c_str();
			cout << setw(10) << StaffInfo[i]->getTimeEnd()[j].c_str();
			cout << setw(11) << setprecision(2) << fixed << StaffInfo[i]->getWorkTime()[j];
			cout << endl;
			++y;
		}
		cout << endl;
	}
}

bool FindStaff(vector <Staff*> &StaffInfo, string findStr)
{
	bool result = false;
	for (unsigned int i = 0; i < StaffInfo.size(); ++i)
	{
		if (StaffInfo[i]->getName().find(findStr) != -1) { 
			cout << "\t" << StaffInfo[i]->getName().c_str() << endl;
			result = true;
		}
	}
	return result;
}