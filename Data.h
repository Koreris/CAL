#ifndef DATA_H_
#define DATA_H_

#include "includes.h"

using namespace std;

long stol(string txt);

/**
 * @brief Data class
 *
 * A date object consists of basically 6 integers, which hold the year, month, day, hour, minute and second.\n
 * It has the necessary member functions for handling those variables, compare dates, and misc functions.
 */
class Data
{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

public:
	/** @name Constructors
	 */
	///@{
	Data();
	Data(string cfg_str);
	Data(int year, int month, int day, int hour, int minute, int second);
	///@}
	/** @name Getters
	*/
	///@{
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	///@}
	/** @name Setters
	*/
	///@{
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);
	void setSecond(int second);
	///@}

	/** @name Operator overloads
	 */
	///@{
	bool operator<(Data date2) const;
	bool operator>(Data date2) const;
	bool operator==(Data date2) const;
	friend ostream& operator<<(ostream& os, const Data& d);
	friend istream& operator>>(istream &is, Data& date);
	///@}

	string str() const;
	string cfg_str() const;


	/** @name Static functions
	 */
	///@{
	static int daysInMonth(int month, int year);
	static bool isLeapYear(int year);
	static Data curData();
	static int numDays(Data d1, Data d2);
	///@}

	/** @name Exceptions
	 */
	///@{
	class InvalidData
	{
	public:
		InvalidData()
	{
	}
	};
	///@}
};

#endif //_DATA_H_
