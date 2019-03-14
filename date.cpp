#include "date.h"
#include <iomanip>
#include <sstream>
using namespace std;

int Date::Year() const { 
	return year;
}
int Date::Month() const {
	return month;
}
int Date::Day() const {
	return day;
}
Date::Date(const int& new_year, const int& new_month, const int& new_day) {
	if (new_year > 9999 || new_year < 0) {
		throw logic_error("Year value is invalid: " + to_string(new_year));
	}
	year = new_year;
	if (new_month > 12 || new_month < 1) {
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1) {
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}
	day = new_day;
}

bool operator== (const Date& lhs, const Date& rhs) {
	return (lhs.Year() == rhs.Year() && lhs.Month() == rhs.Month() && lhs.Day() == rhs.Day());
}
bool operator!= (const Date& lhs, const Date& rhs) {
	return (!(lhs == rhs));
}
bool operator< (const Date& lhs, const Date& rhs) {
	return ((lhs.Year() < rhs.Year()) || (lhs.Year() == rhs.Year() && lhs.Month() < rhs.Month()) || (lhs.Year() == rhs.Year()
		&& lhs.Month() == rhs.Month() && lhs.Day() < rhs.Day()));
}
bool operator<= (const Date& lhs, const Date& rhs) {
	return (lhs < rhs || lhs == rhs);
}
bool operator> (const Date& lhs, const Date& rhs) {
	return (!(lhs <= rhs));
}
bool operator>= (const Date& lhs, const Date& rhs) {
	return (!(lhs < rhs));
}

ostream& operator<< (ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.Year() << "-"
		<< setw(2) << setfill('0') << date.Month() << "-" 
		<< setw(2) << setfill('0') << date.Day();
	return stream;
}
