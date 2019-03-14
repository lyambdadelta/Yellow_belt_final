#pragma once
#include <iostream>
#include <sstream>
#include "date.h"
using namespace std;
class Date {
public:
	int Year() const;
	int Month() const;
	int Day() const;
	Date(const int& new_year, const int& new_month, const int& new_day);
private:
	int year, month, day;
};

bool operator< (const Date& lhs, const Date& rhs);
bool operator<= (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);

ostream& operator<< (ostream& stream, const Date& date);

template <typename T>
Date ParseDate(T& date_stream) {
	bool flag = true;
	int year;
	flag = flag && (date_stream >> year);
	flag = flag && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int month;
	flag = flag && (date_stream >> month);
	flag = flag && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int day;
	flag = flag && (date_stream >> day);
	flag = flag && (date_stream.eof() || date_stream.peek() == ' ');

	if (!flag) {
		throw logic_error("Wrong date format: ");
	}
	return Date(year, month, day);
}
