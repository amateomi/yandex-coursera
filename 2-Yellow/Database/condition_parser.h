#ifndef DATABASE__CONDITION_PARSER_H_
#define DATABASE__CONDITION_PARSER_H_

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

#endif //DATABASE__CONDITION_PARSER_H_
