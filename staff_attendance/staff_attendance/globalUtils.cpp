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

// �����������
void coutWelcome()
{
	cout << "\n\n\n\n\n\t\t\t��������� ������\n";
	cout << "\t\t����� � ������������ �����������";
	cout << "\n\n\n\n\n��� ����, ����� ������, �������� ����� ������� . . .";
}

// ���������� ���� ������ � �������
void SetConsoleTextColor(HANDLE hStdout, int color)
{
	SetConsoleTextAttribute(hStdout, color |
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

// ��������������� ������� ��� ����������� ����� (������ �����)
bool test(char ch, const char *keys, unsigned int size)
{
	for (size_t i = 0; i<size; i++)
	if (keys[i] == ch) return true;
	return false;
}

// ���� ������ ����
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


// ����� ������ ����
int getMode(unsigned int countMode)
{
	unsigned int mode = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << "\n\n ��� ����� (������� �����) ==> ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		mode = getNumber();

		if ((mode > countMode) || (mode == 0))
		{
			SetConsoleTextColor(hStdout, FOREGROUND_RED);
			cout << "������� �������� �� ������������� ������� ���� !";
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		}
		else break;
	}

	return mode;
}

// ������ �� �����
int read_file(char *fileName, vector <Staff*> &StaffInfo)
{		
	ifstream file;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	string tempStr;
	bool isWorkTime = false;
	int countStaff = 0;

	file.open(fileName, ios::in);
	if (!file.is_open()) // ���� ���� �� ������
	{
		SetConsoleTextColor(hStdout, FOREGROUND_RED);
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		return 0;
	}
	else
	{
		StaffInfo.clear();

		while (!file.eof()) //���������� � �����
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

//������ � ����
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
	cout << "\n������ �����������\n";
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
	cout << "\n����� ���������� � ������ ���������\n";
	cout << "\n�����         ���                     ����      ������     ����     �-�� �����";
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





// ����� �� ����� �������� 
void coutMarks(int countExp, int countEvent, double **mark)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\t  ";
	for (size_t j = 0; j < countExp; ++j)
	{
		cout << setw(8) << j + 1;
	}

	for (size_t i = 0; i < countEvent; ++i)
	{
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n ������� " << i + 1 << ": ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		for (size_t j = 0; j < countExp; ++j)
		{
			cout << setw(8) << setprecision(5) << fixed << mark[i][j];
		}
	}
}

void coutResult(int size, vector<double *>x)
{
	for (size_t i = 0; i < size; i++)
		cout << "\tvalue [" << i + 1 << "] = " << setprecision(5) << fixed << x[x.size() - 1][i] << endl;
}

double * newX(int countEvent)
{
	double *tempX = new double[countEvent];
	return tempX;
}

double * newK(int countExp)
{
	double *tempK = new double[countExp];
	return tempK;
}

void calcGroupMarks(int countExp, int countEvent, double Eps, double **mark)
{
	double k0 = 0;
	vector<double*> x, k;
	vector<double> lambda;

	double *tempX;// = new double[countEvent];
	double *tempK;// = new double[countExp];
	double tempLambda = 0;

	double isMax = 0;
	int iteration = 1;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	k0 = 1.0 / countExp;

	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n\n ����������� " << iteration;
 	// ������� ������ �����������
	cout << "\n������: ";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	tempX = newX(countEvent);
	for (int i = 0; i < countEvent; ++i)
	{
		tempX[i] = 0;
		for (int j = 0; j < countExp; ++j)
		{
			tempX[i] += mark[i][j];
		}
		tempX[i] *= k0;
		cout << setprecision(5) << fixed << tempX[i] << "  ";
	}
	x.push_back(tempX);

	// ������������� ����������
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n������������� ����������: ";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	for (int i = 0; i < countEvent; ++i)
	{
		double sum = 0;
		for (int j = 0; j < countExp; ++j)
		{
			sum += mark[i][j];
		}
		tempLambda += x[0][i] * sum;
	}
	cout << setprecision(5) << fixed << tempLambda << "  ";
	lambda.push_back(tempLambda);

	// ����. ��������������
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n����. ��������������: ";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	tempK = newK(countExp);
	for (int i = 0; i < countExp; ++i)
	{
		double sum = 0;
		for (int j = 0; j < countEvent; ++j)
		{
			sum += mark[j][i] * x[0][j];
		}
		tempK[i] = (1./lambda[0])* sum;
		cout << setprecision(5) << fixed << tempK[i] << "  ";
	}
	k.push_back(tempK);

	
	do
	{
		iteration++;
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n\n ����������� " << iteration;
		// ������� ������ �����������
		cout << "\n������: ";
		tempX = newX(countEvent);
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		for (int i = 0; i < countEvent; ++i)
		{
			tempX[i] = 0;
			for (int j = 0; j < countExp; ++j)
			{
				tempX[i] += mark[i][j] * k[k.size() - 1][j];
			}
			cout << setprecision(5) << fixed << tempX[i] << "  ";
		}
		x.push_back(tempX);

		// ������������� ����������
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n������������� ����������: ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		tempLambda = 0;
		for (int i = 0; i < countEvent; ++i)
		{
			double sum = 0;
			for (int j = 0; j < countExp; ++j)
			{
				sum += mark[i][j];
			}
			tempLambda += x[x.size() - 1][i] * sum;
		}
		cout << setprecision(5) << fixed << tempLambda << "  ";
		lambda.push_back(tempLambda);

		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		// ����. ��������������
		cout << "\n����. ��������������: ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		tempK = newK(countExp);
		for (int i = 0; i < countExp; ++i)
		{
			double sum = 0;
			for (int j = 0; j < countEvent; ++j)
			{
				sum += mark[j][i] * x[x.size() - 1][j];
			}
			tempK[i] = (1. / lambda[lambda.size() - 1])* sum;
			cout << setprecision(5) << fixed << tempK[i] << "  ";
		}
		k.push_back(tempK);

		isMax = abs(x[x.size() - 1][0] - x[x.size() - 2][0]);
		for (int j = 1; j < countEvent; ++j)
		{
			if (abs(x[x.size() - 1][j] - x[x.size() - 2][j]) > isMax)
				isMax = abs(x[x.size() - 1][j] - x[x.size() - 2][j]);
		}

	} while (isMax >= Eps);

	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n\n ���������: " << endl;
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	coutResult(countEvent, x);
}
