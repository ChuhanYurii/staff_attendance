// staff_attendance.cpp: ���������� ����� ����� ��� ����������� ����������.
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

	// �����������
	coutWelcome();
	_getch();

	// ������ � �������������
	while (true)
	{
		system("cls");
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << ">�������� ����������� ��������.\n";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		cout << "\n\t1. �������� ������ �����������";
		cout << "\n\t2. �������� ������� ������� � ����� � ������";
		cout << "\n\t3. ����� ���������� � ������ ��������� ";
		cout << "\n\t4. ���������� ��������� ";
		cout << "\n\t5. �������������� ���������� � ��������� ";
		cout << "\n\t6. �������� ��������� ";
		cout << "\n\t7. ���������� ������ ���������� �� ����� ";
		cout << "\n\t7. ����� ��������� �� ����� ";
		cout << "\n\t8. ������� ����������";
		cout << "\n\t9. ��������� ��������";
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
				
		int downloadMode = getMode(9);
		string tempStr = "";
		
		read_file("staff.txt", StaffInfo);
		
		switch (downloadMode)
		{
		case 1: // �������� ������ �����������
			ShowStaffList(StaffInfo);
			break;

		case 4:
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n ������� ��� ������ ��������� ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			getline(cin, tempStr);
			StaffInfo.push_back(new Staff());
			StaffInfo[StaffInfo.size() - 1]->setID(StaffInfo.size());
			StaffInfo[StaffInfo.size() - 1]->setName(tempStr);
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n ����� �������� �������� ";
			break;
		 
		default:
			break;
		}

		write_file("staff.txt", StaffInfo);

		_getch();
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "\n\n>--------------------------------------------------";
		cout << "\n\t��� ������ - ������� ESC";
		cout << "\n\t��� ������ �������� - ������� ����� �������";

		char c;
		c = _getch();
		if (c == 27) break;
		else continue;
	}
	
	
	return 0;
}

