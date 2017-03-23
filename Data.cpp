#include "Data.h"

/**
* Doesn't have error checking, assumes the string contains only digits and a possible minus sign in the beggining.
* @brief Converts string to long
* @param txt string to convert
* @return long with the value
*/
long stol(string txt)
{
	stringstream ss(txt);
	long num { };
	ss >> num;

	return num;
}

/**
 * This constructor leads to an invalid date, not possible with setters or the other constructors because of the exceptions
 * @brief Invalid Data empty constructor
 */
Data::Data()
{
	year = -1;
	month = -1;
	day = -1;
	hour = -1;
	minute = -1;
	second = -1;
}
/**
 * This constructor makes a date object out of a properly formatted string
 * @brief Constructor to make date object out of string
 * @param cfg_str formatted string to make a Data object
 */
Data::Data(string cfg_str)
{
	cfg_str += "\n";
	stringstream ss(cfg_str);

	string temp;

	getline(ss, temp, ' ');
	year = stol(temp);

	getline(ss, temp, ' ');
	month = stol(temp);

	getline(ss, temp, ' ');
	day = stol(temp);

	getline(ss, temp, ' ');
	hour = stol(temp);

	getline(ss, temp, ' ');
	minute = stol(temp);

	getline(ss, temp, ' ');
	second = stol(temp);

	if (year < 1900)
		throw InvalidData();
	if (month < 1 || month > 12)
		throw InvalidData();
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidData();
	if (hour < 0 || hour > 23)
		throw InvalidData();
	if (minute < 0 || minute > 59)
		throw InvalidData();
	if (second < 0 || second > 59)
		throw InvalidData();
}
/**
 * Throws an appropriate exception if any of the parameters are invalid
 * @brief Valid Data constructor
 *
 * @param year Year
 * @param month Month
 * @param day Day
 * @param hour Hour
 * @param minute Minute
 * @param second Second
 */
Data::Data(int year, int month, int day, int hour, int minute, int second)
{
	if (year < 1900)
		throw InvalidData();
	if (month < 1 || month > 12)
		throw InvalidData();
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidData();
	if (hour < 0 || hour > 23)
		throw InvalidData();
	if (minute < 0 || minute > 59)
		throw InvalidData();
	if (second < 0 || second > 59)
		throw InvalidData();

	this->year = year;
	this->month = month;
	this->day = day;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

// Getters
/**
 * @brief Returns the year
 *
 * @return integer with the year
 */
int Data::getYear() const
{
	return this->year;
}
/**
 * @brief Returns the month
 *
 * @return integer with the month
 */
int Data::getMonth() const
{
	return this->month;
}
/**
 * @brief Returns the day
 *
 * @return integer with the day
 */
int Data::getDay() const
{
	return this->day;
}
/**
 * @brief Returns the hour
 *
 * @return integer with the hour
 */
int Data::getHour() const
{
	return this->hour;
}
/**
 * @brief Returns the minute
 *
 * @return integer with the minute
 */
int Data::getMinute() const
{
	return this->minute;
}
/**
 * @brief Returns the second
 *
 * @return integer with the second
 */
int Data::getSecond() const
{
	return this->second;
}

// Setters

/**
 * Throws InvalidData exception if the year is invalid
 * @brief Sets the year
 *
 * @param year Year
 */
void Data::setYear(int year)
{
	if (year < 1900)
		throw InvalidData();

	this->year = year;
}

/**
 * Throws InvalidData exception if the month is invalid
 * @brief Sets the month
 *
 * @param month Month
 */
void Data::setMonth(int month)
{
	if (month < 1 || month > 12)
		throw InvalidData();

	this->month = month;
}

/**
 * Throws InvalidData exception if the day is invalid
 * @brief Sets the day
 *
 * @param day Day
 */
void Data::setDay(int day)
{
	if (day < 1 || day > daysInMonth(month, year))
		throw InvalidData();

	this->day = day;
}

/**
 * Throws InvalidData exception if the hour is invalid
 * @brief Sets the hour
 *
 * @param hour Hour
 */
void Data::setHour(int hour)
{
	if (hour < 0 || hour > 23)
		throw InvalidData();

	this->hour = hour;
}

/**
 * Throws InvalidData exception if the minute is invalid
 * @brief Sets the minute
 *
 * @param minute Minute
 */
void Data::setMinute(int minute)
{
	if (minute < 0 || minute > 59)
		throw InvalidData();

	this->minute = minute;
}

/**
 * Throws InvalidData exception if the second is invalid
 * @brief Sets the second
 *
 * @param second Second
 */
void Data::setSecond(int second)
{
	if (second < 0 || second > 59)
		throw InvalidData();

	this->second = second;
}

// Operator overloads
/**
 * @brief Less than operator
 *
 * @param date2 Right hand side date
 * @return Returns true if left hand side date is previous in time from the right hand side one, false otherwise.
 */
bool Data::operator<(Data date2) const
{
	if (this->year < date2.year)
		return true;
	else if (this->year > date2.year)
		return false;
	else if (this->month < date2.month)
		return true;
	else if (this->month > date2.month)
		return false;
	else if (this->day < date2.day)
		return true;
	else if (this->day > date2.day)
		return false;
	else if (this->hour < date2.hour)
		return true;
	else if (this->hour > date2.hour)
		return false;
	else if (this->minute < date2.minute)
		return true;
	else if (this->minute > date2.minute)
		return false;
	else if (this->second < date2.second)
		return true;
	else
		return false;
}
/**
 * @brief Greater than operator
 *
 * @param date2 Right hand side date
 * @return Returns true if left hand side date is after the right hand side one in time, false otherwise.
 */
bool Data::operator>(Data date2) const
{
	if (this->year > date2.year)
		return true;
	else if (this->year < date2.year)
		return false;
	else if (this->month > date2.month)
		return true;
	else if (this->month < date2.month)
		return false;
	else if (this->day > date2.day)
		return true;
	else if (this->day < date2.day)
		return false;
	else if (this->hour > date2.hour)
		return true;
	else if (this->hour < date2.hour)
		return false;
	else if (this->minute > date2.minute)
		return true;
	else if (this->minute < date2.minute)
		return false;
	else if (this->second > date2.second)
		return true;
	else
		return false;
}
/**
 * @brief Equal comparison operator
 *
 * @param date2 Right hand side date
 * @return Returns true if the dates are the same, false otherwise
 */
bool Data::operator== (Data date2) const
{
	return (year == date2.year && month == date2.month && day == date2.day && hour == date2.hour && minute == date2.minute && second == date2.second);
}
/**
 * Sends to the output stream the string with the date, returned by cfg_str()
 * @brief Bitshift operator <<
 * @param os left hand side output stream
 * @param d right hand side date
 * @return the output stream os
 */
ostream& operator<<(ostream& os, const Data& d)
{
	return os << d.cfg_str();
}
/**
 * Reads a date from the input stream is in the format YYYY MM DD hh mm ss
 * @brief Bitshift operator >>
 * @param is left hand side input stream
 * @param date right hand side date
 * @return the input stream is
 */
istream& operator >>(istream &is, Data& date)
{
	char c1 { ' ' };
	int year { };
	int month { };
	int day { };
	int hour { };
	int minute { };
	int second { };

	is >> year >> c1 >> month >> c1 >> day >> c1 >> hour >> c1 >> minute >> c1 >> second;

	Data d(year, month, day, hour, minute, second);

	date = d;

	return is;
}
/**
 * Returns a string with a date in the format YYYY/MM/DD - hh:mm:ss
 * @brief Formatted date string
 *
 * @return a string with the formatted date
 */
string Data::str() const
{
	stringstream ss;

	ss << year << "/" << month << "/" << day << " - " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << minute << ":"  << setfill('0')<< setw(2) << second;

	return ss.str();
}
/**
 * Returns a string in the format YYYY MM DD hh mm ss to be used in the config file
 * @brief Space separated date
 * @return a string with the date
 */
string Data::cfg_str() const
{
	stringstream ss;

	ss << year << " " << month << " " << day << " " << hour << " " << minute << " " << second;

	return ss.str();
}

/// Static function
/**
 * Returns the number of days in a month, taking into account if it is a leap year or not
 * @brief Number of days in a month
 * @param month month (1-12)
 * @param year year
 * @return number of days
 */
int Data::daysInMonth(int month, int year)
{
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2) {
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	} else
		return 31;
}

/**
 * @brief Checks if year is leap year
 * @param year year
 * @return true if it is leap year, false otherwise
 */
bool Data::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Returns a date with the current computer local date and time
 * @brief Current local date and time
 * @return date corresponding to the current date
 */
Data Data::curData()
{
	time_t t = time(0); // Get current time
	struct tm *t_now = localtime(&t);

	int year { t_now->tm_year + 1900 };
	int month { t_now->tm_mon + 1 };
	int day { t_now->tm_mday };
	int hour { t_now->tm_hour };
	int minute { t_now->tm_min };
	int second { t_now->tm_sec };

	Data temp(year, month, day, hour, minute, second);

	return temp;
}
/**
 * Returns the number of days difference between two dates
 * @brief Number of days difference between two dates
 * @param d1 a date
 * @param d2 a date
 * @return number of days
 */
int Data::numDays(Data d1, Data d2)
{
	if (d1.getYear() == d2.getYear())
	{ //same year?
		if (d1.getMonth() == d2.getMonth())
		{  //same month?
			if (d1.getDay() > d2.getDay())
			{ //same month
				return d1.getDay() - d2.getDay();
			} else
				return d2.getDay() - d1.getDay();
		} else
		{ //different month
			int somadaysbetweenmonths { 0 };
			if (d1.getMonth() > d1.getMonth())
			{
				for (int i = d2.getMonth() + 1;
						i < (d1.getMonth() - d2.getMonth()) + d2.getMonth(); i++)
				{
					somadaysbetweenmonths = somadaysbetweenmonths
							+ Data::daysInMonth(i, d1.getYear());
				}
				return somadaysbetweenmonths
						+ (Data::daysInMonth(d1.getMonth(), d1.getYear()) - d1.getDay())
						+ d2.getDay();
			} else
			{
				for (int i = d1.getMonth() + 1;
						i < (d2.getMonth() - d1.getMonth()) + d1.getMonth(); i++)
				{
					somadaysbetweenmonths = somadaysbetweenmonths
							+ Data::daysInMonth(i, d2.getYear());
				}
				return somadaysbetweenmonths
						+ (Data::daysInMonth(d2.getMonth(), d2.getYear()) - d2.getDay())
						+ d1.getDay();
			}
		}
	} else
	{
		Data date1(d1);
		Data date2(d2);

		if (d1.getYear() > d2.getYear())
		{
			Data date3(d2);
			date2 = d1;
			date1 = date3;
		}


		int days { Data::daysInMonth(date1.getMonth(), date1.getYear())
				- date1.getDay() };


		for (unsigned int i = date1.getMonth() + 1; i <= 12; i++)
		{
			days += Data::daysInMonth(i, date1.getYear());
		}


		for (int i = date1.getYear() + 1; i < date2.getYear(); i++)
		{
			if (Data::isLeapYear(i))
				days += 366;
			else
				days += 365;
		}


		for (int i = 1; i < date2.getMonth(); i++)
		{
			days += Data::daysInMonth(i, date2.getYear());
		}


		days += date2.getDay();

		return days;
	}
}

