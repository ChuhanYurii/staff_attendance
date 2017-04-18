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

void ShowStaffInfoList(vector <Staff*> &StaffInfo);

bool FindStaff(vector <Staff*> &StaffInfo, string findStr);