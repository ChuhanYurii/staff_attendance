#include <vector>

using namespace std;

class Staff
{
private:
	int id;
	string Name;
	vector <string> dateWork;
	vector <string> timeBegin;
	vector <string> timeEnd;
	vector <double> workTime;
	double allWorkTime;
public:

	void setName(string newName)
	{
		Name = newName;
	}

	string getName()
	{
		return Name;
	}

	void setID(int newID)
	{
		id = newID;
	}

	int getID()
	{
		return id;
	}

	void setDate(string newDate)
	{
		dateWork.push_back(newDate);
	}

	vector <string> getDate()
	{
		return dateWork;
	}

	void setTimeBegin(string newTime)
	{
		timeBegin.push_back(newTime);
	}

	vector <string> getTimeBegin()
	{
		return timeBegin;
	}

	void setTimeEnd(string newTime)
	{
		timeEnd.push_back(newTime);
	}

	vector <string> getTimeEnd()
	{
		return timeEnd;
	}

	void setWorkTime()
	{
		int hourBegin, minuteBegin, hourEnd, minuteEnd;
		for (size_t i = 0; i < dateWork.size(); ++i)
		{
			string tempStr = timeBegin[i].substr(0,2);
			hourBegin = atoi(tempStr.c_str());

			tempStr = timeBegin[i].substr(3,2);
			minuteBegin = atoi(tempStr.c_str());

			tempStr = timeEnd[i].substr(0,2);
			hourEnd = atoi(tempStr.c_str());

			tempStr = timeEnd[i].substr(3,2);
			minuteEnd = atoi(tempStr.c_str());

			if (minuteEnd - minuteBegin < 0) workTime.push_back(hourEnd - hourBegin - 1 + 1. * (60 + minuteEnd - minuteBegin) / 60); 
			else workTime.push_back(hourEnd - hourBegin + 1. * (minuteEnd - minuteBegin) / 60);
		}
		SetAllWorkTime();
	}

	vector <double> getWorkTime()
	{
		return workTime;
	}

	void SetAllWorkTime()
	{
		double result = 0;
		for (size_t i = 0; i < workTime.size(); ++i)
		{
			result += workTime[i];
		}
		allWorkTime = result;
	}

	double getAllWorkTime()
	{
		return allWorkTime;
	}

};