#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iomanip>
#include <vector>

using namespace std;

// приветствие
void coutWelcome()
{
	cout << "\t\t\tПроектная работа\n";
	cout << "\n\n\n\n\n";
	cout << "   В задании реализована обработка экспертных оценок двумя методами:\n\n";
	cout <<	"\t- групповая экспертная оценка при непосредственном оценивании\n";
	cout << "\t- обработка парных сравнений\n";
	cout << "\n\n\nДля того, чтобы начать, нажммите любую клавишу . . .";
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

double getDoublePair()
{
	char numbers[4] = { '0', '1', '5', ',' };
	string n;
	char ch;

	while ((ch = _getch()) != '\r')//enter
	if (test(ch, numbers, 4))
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
		cout << "\n\n Ваш выбор (введите цифру) ==> ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		mode = getNumber();

		if ((mode > countMode) || (mode == 0))
		{
			SetConsoleTextColor(hStdout, FOREGROUND_RED);
			cout << "Введёное значение не соответствует пунктам меню !";
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		}
		else break;
	}

	return mode;
}

void inputMarks(int countExp, int countEvent, double **&mark)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i < countExp; ++i)
	{
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n  Oценки Эксперта № " << i + 1 << endl;
		for (size_t j = 0; j < countEvent; ++j)
		{
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "    событие " << j + 1 << " ==> ";
			SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
			mark[j][i] = getDouble();
		}
	}
}

// вывод на экран значений 
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
		cout << "\n событие " << i + 1 << ": ";
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
	cout << "\n\n Приближение " << iteration;
 	// средние оценки приближения
	cout << "\nОценки: ";
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

	// нормированный коефициент
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nНормированный коефициент: ";
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

	// коеф. компетентности
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nКоеф. компетентности: ";
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
		cout << "\n\n Приближение " << iteration;
		// средние оценки приближения
		cout << "\nОценки: ";
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

		// нормированный коефициент
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\nНормированный коефициент: ";
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
		// коеф. компетентности
		cout << "\nКоеф. компетентности: ";
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
	cout << "\n\n Результат: " << endl;
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	coutResult(countEvent, x);
}

 

void inputMarksPair(int countExp, int countEvent, double **&mark)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i < countExp; ++i)
	{
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n  Оценки парного сравнения от Эксперта № " << i + 1 << endl;
		for (size_t j = 0; j < countEvent; ++j)
		{
			for (size_t q = 0; q < countEvent; ++q)
			{
				if (q != j)
				{
					SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
					cout << "    события " << j + 1 << " и " << q + 1 << " ==> ";
					SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
					mark[i][j * countEvent * countEvent + q] = getDoublePair();
				}
				else mark[i][j * countEvent * countEvent + q] = 0.5;
			}
		}
	}
}

void coutMarksPair(int countExp, int countEvent, double **mark)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	
	for (size_t i = 0; i < countExp; ++i)
	{
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n\n  Оценки Эксперта № " << i + 1 << endl;
		cout << "\t   ";
		for (size_t j = 0; j < countEvent; ++j)
		{
			cout << setw(5) << j + 1;
		}

		for (size_t j = 0; j < countEvent; ++j)
		{
			SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
			cout << "\n событие " << j + 1 << ": ";
			for (size_t q = 0; q < countEvent; ++q)
			{
				SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
				cout << setw(5) << mark[i][j * countEvent * countEvent + q];
			}
		}
	}
}

void calcPairMarks(int countExp, int countEvent, double Eps, double **markPair)
{
	double k0 = 0;
	vector<double*> x, k;
	vector<double> lambda;
	
	double ** mark;
	mark = new double*[countEvent];
	for (size_t j = 0; j < countEvent; j++)
	{
		mark[j] = new double[countEvent];
	}

	int count0 = 0, count1 = 0;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n\n Математическое ожидание\n ";
	cout << "\t   ";
	for (size_t j = 0; j < countEvent; ++j)
	{
		cout << setw(8) << j + 1;
	}
	for (size_t j = 0; j < countEvent; ++j)
	{
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n событие " << j + 1 << ": ";
		for (size_t q = 0; q < countEvent; ++q)
		{
			count0 = 0, count1 = 0;
			for (size_t i = 0; i < countExp; ++i)
			{
				if (markPair[i][j * countEvent * countEvent + q] == 0) count0++;
				if (markPair[i][j * countEvent * countEvent + q] == 1) count1++;
			}

			mark[j][q] = 0.5 + 1.0 * (count1 - count0) / (2 * countExp);
			cout << setw(8) << setprecision(4) << fixed << mark[j][q];
		}
	}

	
	double *tempX;// = new double[countEvent];
	double *tempK;// = new double[countExp];
	double tempLambda = 0;

	double isMax = 0;
	int iteration = 1;
	
	k0 = 1.0;

	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n\n Приближение " << iteration;
	cout << "\nY: ";
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

	// нормированный коефициент
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nНормированный коефициент: ";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	for (int i = 0; i < countEvent; ++i)
	{
		tempLambda += x[0][i];
	}
	cout << setprecision(5) << fixed << tempLambda << "  ";
	lambda.push_back(tempLambda);

	// коеф. относительной важности
	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\nКоеф. относительной важности: ";
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	tempK = newK(countEvent);
	for (int i = 0; i < countEvent; ++i)
	{
		tempK[i] = (1. / lambda[0])* x[0][i];
		cout << setprecision(5) << fixed << tempK[i] << "  ";
	}
	k.push_back(tempK);

	do
	{
		iteration++;
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\n\n Приближение " << iteration;
		
		cout << "\nY: ";
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

		// нормированный коефициент
		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		cout << "\nНормированный коефициент: ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		tempLambda = 0;
		for (int i = 0; i < countEvent; ++i)
		{
			tempLambda += x[x.size() - 1][i];
		}
		cout << setprecision(5) << fixed << tempLambda << "  ";
		lambda.push_back(tempLambda);

		SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
		// коеф. относительной важности
		cout << "\nКоеф. относительной важности: ";
		SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
		tempK = newK(countEvent);
		for (int i = 0; i < countEvent; ++i)
		{
			tempK[i] = (1. / lambda[lambda.size() - 1])* x[x.size() - 1][i];
			cout << setprecision(5) << fixed << tempK[i] << "  ";
		}
		k.push_back(tempK);

		isMax = abs(k[k.size() - 1][0] - k[k.size() - 2][0]);
		for (int j = 1; j < countEvent; ++j)
		{
			if (abs(k[k.size() - 1][j] - k[k.size() - 2][j]) > isMax)
				isMax = abs(k[k.size() - 1][j] - k[k.size() - 2][j]);
		}

	} while (isMax >= Eps);

	SetConsoleTextColor(hStdout, FOREGROUND_BLUE);
	cout << "\n\n Результат: " << endl;
	SetConsoleTextColor(hStdout, FOREGROUND_GREEN);
	coutResult(countEvent, k); 
}
