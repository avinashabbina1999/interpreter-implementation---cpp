#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "lib/reglex.h"
#include "binop_node.h"
#include <sstream>

class ConditionNode : public BinopNode{
public:
  virtual ASTResult apply(const ASTResult &lhs, const ASTResult &rhs);
  ConditionNode(const std::string &cond);
private:
  std::string _cond;
};

#endif