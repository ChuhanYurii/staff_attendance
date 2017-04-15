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

};