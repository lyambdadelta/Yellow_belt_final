#include "database.h"
using namespace std;
Database::Database() {};
void Database::Add(const Date& date, const string& event) {
	if (!database[date].count(event)) {
		database[date].insert(event);
		database_history[date].push_back(event);
	}
}
void Database::Print(ostream& out) const {
	for (auto dat : database_history) {
		for (auto ev : dat.second) {
			out << dat.first << " " << ev << endl;
		}
	}
}
pair<Date, string> Database::Last(const Date& date) const {
	auto it = database.upper_bound(date);
	if (it != database.begin()) {
		it--;
		return make_pair(it->first, database_history.at(it->first).back());
	}
	else {
		throw invalid_argument("Leastest date");
	}
}

