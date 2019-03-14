#pragma once
#include "date.h"
#include <string>
#include <memory>
#include <utility>
#include <tuple>
using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};



template <typename T>
bool Compare(Comparison cmp_, const T& lhs, const T& rhs) {
	if (cmp_ == Comparison::Less) {
		return lhs < rhs;
	}
	else if (cmp_ == Comparison::LessOrEqual) {
		return lhs <= rhs;
	}
	else if (cmp_ == Comparison::Greater) {
		return lhs > rhs;
	}
	else if (cmp_ == Comparison::GreaterOrEqual) {
		return lhs >= rhs;
	}
	else if (cmp_ == Comparison::Equal) {
		return lhs == rhs;
	}
	else if (cmp_ == Comparison::NotEqual) {
		return lhs != rhs;
	}
	else {
		throw logic_error("Unknown Comparsion (node.h)");
	}
}

enum class LogicalOperation {
	Or,
	And,
};

class Node {
public:
	Node();
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node {
public:
	EmptyNode();
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date);
	bool Evaluate(const Date& date, const string& event) override;
private:
	const Date date_;
	const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp, const string& event);
	bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison cmp_;
	const string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> lhs, const shared_ptr<Node> rhs);
	bool Evaluate(const Date& date, const string& event) override;
private:
	const LogicalOperation op_;
	const shared_ptr<Node> lhs_, rhs_;
};
