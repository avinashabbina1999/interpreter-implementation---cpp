#ifndef ARRAY_ASSIGN_NODE_H
#define ARRAY_ASSIGN_NODE_H

#include "ast_node.h"
#include "lib/reglex.h"
#include "array_node.h"
#include <stdexcept>

class ArrayAssignNode : public ASTNode{
  public:
    ArrayAssignNode(const std::string &id, int ind, ASTNode *val);
    ArrayAssignNode(const std::string &id, ASTNode *node, ASTNode *val);
    ASTResult eval(RefEnv *env);
  private:
    std::string _id;
    int _ind;
    ASTNode *_node;
    ASTNode *_val;
};

#endif