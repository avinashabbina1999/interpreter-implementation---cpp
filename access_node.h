#ifndef ACCESS_NODE_H
#define ACCESS_NODE_H

#include "ast_node.h"
#include "lib/reglex.h"
#include "array_node.h"
#include "ref_node.h"
#include <sstream>

class AccessNode : public ASTNode{
public:
  AccessNode(const std::string &id,int ind);
  AccessNode(const std::string &id,ASTNode *node);
  // evaluate the function - insert itself into the RefEnv
  virtual ASTResult eval(RefEnv *env);
private:
  std::string _id;
  int _ind;
  ASTNode *_node;
};

#endif