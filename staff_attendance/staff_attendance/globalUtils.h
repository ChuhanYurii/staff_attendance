#include <vector>
#include "ClassStaff.h"

void coutWelcome();

void SetConsoleTextColor(HANDLE hStdout, int color);

bool test(char ch, const char *keys, unsigned int size);

int getNumber();

double getDouble();

int getMode(unsigned int countMode);

int read_file(char *fileName, std::vector <Staff*> &StaffInfo);

void write_file(char *fileName, vector <Staff*> &StaffInfo);

void ShowStaffList(vector <Staff*> &StaffInfo);




void coutMarks(int countExp, int countEvent, double **mark);

void calcGroupMarks(int countExp, int countEvent, double Eps, double **mark);

void coutResult(int countEvent, std::vector<double*> x);


void coutMarksPair(int countExp, int countEvent, double **mark);