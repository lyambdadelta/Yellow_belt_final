#pragma once
#include "date.h"
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

template <typename t1, typename t2>
ostream& operator<< (ostream& stream, const pair<t1, t2> pair) {
	stream << pair.first << " " << pair.second;
	return stream;
}

class Database {
public:
	Database();
	void Add(const Date& date, const string& event);
	void Print(ostream& out) const;
	template <class func>
	int RemoveIf(func predicate) {
		int count = 0;
		map <Date, vector<string>::iterator> history_delete;
		for (auto x : database_history) {
			auto it = stable_partition(database_history[x.first].begin(), database_history[x.first].end(), [x, predicate](string event) {
				return !predicate(x.first, event);
			});
			for (auto er = it; er != database_history[x.first].end(); er++) {
				database[x.first].erase(*er);
				count++;
			}
			if (!database[x.first].size()) {
				database.erase(x.first);
			}
			history_delete[x.first] = it;
		}
		for (auto x : history_delete) {
			database_history[x.first].erase(x.second, database_history[x.first].end());
			if (!database_history[x.first].size()) {
				database_history.erase(x.first);
			}
		}
		return count;
	}
	template <class func>
	set<pair<Date, string>> FindIf(func predicate) const {
		set<pair<Date, string>> res;
		for (auto x : database) {
			for (auto y : x.second) {
				if (predicate(x.first, y)) {
					res.insert(pair<Date, string>(x.first, y));
				}
			}
		}
		return res;
	}
	pair<Date, string> Last(const Date& date) const;
private:
	map<Date, set<string>> database;
	map<Date, vector<string>> database_history;
};
