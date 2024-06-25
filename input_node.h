#ifndef INPUT_NODE_H
#define INPUT_NODE_H

#include "lib/reglex.h"
#include "ast_node.h"
#include <string.h>
#include <iostream>
#include <sstream>

class InputNode : public ASTNode{
public:
  InputNode(const std::string &input,const std::string &id);
  InputNode(const std::string &id);
  ASTResult eval(RefEnv *env);
private:
  std::string _input;
  std::string _id;
};

#endif