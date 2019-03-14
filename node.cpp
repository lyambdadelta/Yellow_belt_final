#include "node.h"

Node::Node() {};
EmptyNode::EmptyNode() {};
bool EmptyNode::Evaluate(const Date& date, const string& event) { return true; };

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) : cmp_(cmp), date_(date) 
{

};
bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
	return (Compare(cmp_, date, date_));
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) : cmp_(cmp), event_(event) {};
bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
	return Compare(cmp_, event, event_);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> lhs, const shared_ptr<Node> rhs)
	: op_(op), lhs_(lhs), rhs_(rhs) {};
bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
	return (op_ == LogicalOperation::And) ? lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event)
		: lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event);
}
