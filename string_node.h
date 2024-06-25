#ifndef STRING_NODE_H
#define STRING_NODE_H

#include "lib/reglex.h"
#include "ast_node.h"
#include <string.h>

class StringNode : public ASTNode{
public:
  StringNode(const std::string &input);
  ASTResult eval(RefEnv *env);
  std::string get_string() const;
private:
  std::string _input;
};

#endif