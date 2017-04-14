#include <vector>

void coutWelcome();

void SetConsoleTextColor(HANDLE hStdout, int color);

bool test(char ch, const char *keys, unsigned int size);

int getNumber();

double getDouble();

int getMode(unsigned int countMode);

void inputMarks(int countExp, int countEvent, double **&mark);

void coutMarks(int countExp, int countEvent, double **mark);

void calcGroupMarks(int countExp, int countEvent, double Eps, double **mark);

void coutResult(int countEvent, std::vector<double*> x);


void inputMarksPair(int countExp, int countEvent, double **&mark);

void coutMarksPair(int countExp, int countEvent, double **mark);

void calcPairMarks(int countExp, int countEvent, double Eps, double **markPair);
