#ifndef DISPLAY_NODE_H
#define DISPLAY_NODE_H

#include "lib/reglex.h"
#include "ast_node.h"
#include <string.h>
#include <iostream>

class DisplayNode : public ASTNode{
public:
  DisplayNode(const std::string &input);
  DisplayNode(ASTNode *node);
  ASTResult eval(RefEnv *env);
private:
  std::string _input;
  ASTNode *_node;
};

#endif