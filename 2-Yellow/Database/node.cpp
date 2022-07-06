#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) {
  return true;
}

DateComparisonNode::DateComparisonNode(Comparison comparison, Date date)
    : comparison_(comparison),
      date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) {
  switch (comparison_) {
    case Comparison::Less:
      return date < date_;

    case Comparison::LessOrEqual:
      return date <= date_;

    case Comparison::Greater:
      return date > date_;

    case Comparison::GreaterOrEqual:
      return date >= date_;

    case Comparison::Equal:
      return date == date_;

    case Comparison::NotEqual:
      return date != date_;

    default:
      throw logic_error("Unknown Comparison operation");
  }
}

EventComparisonNode::EventComparisonNode(Comparison comparison, string event)
    : comparison_(comparison),
      event_(move(event)) {}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
  switch (comparison_) {
    case Comparison::Less:
      return event < event_;

    case Comparison::LessOrEqual:
      return event <= event_;

    case Comparison::Greater:
      return event > event_;

    case Comparison::GreaterOrEqual:
      return event >= event_;

    case Comparison::Equal:
      return event == event_;

    case Comparison::NotEqual:
      return event != event_;

    default:
      throw logic_error("Unknown Comparison operation");
  }
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation operation,
                                           shared_ptr<Node> left,
                                           shared_ptr<Node> right)
    : operation_(operation),
      left_(move(left)),
      right_(move(right)) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
  switch (operation_) {
    case LogicalOperation::Or:
      return left_->Evaluate(date, event) || right_->Evaluate(date, event);

    case LogicalOperation::And:
      return left_->Evaluate(date, event) && right_->Evaluate(date, event);

    default:
      throw logic_error("Unknown LogicalOperation operation");
  }
}
