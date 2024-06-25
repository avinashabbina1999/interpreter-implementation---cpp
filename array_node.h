#ifndef ARRAY_NODE_H
#define ARRAY_NODE_H

#include "lib/reglex.h"
#include "ast_node.h"
#include <vector>

class ArrayNode : public ASTNode{
public:
  // add a parameter to the array
  virtual void add_element(ASTNode *node);

  // evaluate the function - insert itself into the RefEnv
  virtual ASTResult eval(RefEnv *env);

private:
  std::vector<ASTNode*> _param;
};

#endif