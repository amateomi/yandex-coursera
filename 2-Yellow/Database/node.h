#ifndef DATABASE__NODE_H_
#define DATABASE__NODE_H_

#include "date.h"

#include <memory>

class Node {
 public:
  virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node {
 public:
  bool Evaluate(const Date& date, const string& event) override;
};

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

class DateComparisonNode : public Node {
 public:
  DateComparisonNode(Comparison comparison, Date date);

  bool Evaluate(const Date& date, const string& event) override;

 private:
  Comparison comparison_;
  Date date_;
};

class EventComparisonNode : public Node {
 public:
  EventComparisonNode(Comparison comparison, string event);

  bool Evaluate(const Date& date, const string& event) override;

 private:
  Comparison comparison_;
  string event_;
};

enum class LogicalOperation {
  Or,
  And
};

class LogicalOperationNode : public Node {
 public:
  LogicalOperationNode(LogicalOperation operation,
                       shared_ptr<Node> left,
                       shared_ptr<Node> right);

  bool Evaluate(const Date& date, const string& event) override;

 private:
  LogicalOperation operation_;
  shared_ptr<Node> left_, right_;
};

#endif //DATABASE__NODE_H_
