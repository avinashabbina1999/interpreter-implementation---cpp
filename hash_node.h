#ifndef HASH_NODE_H
#define HASH_NODE_H

#include "ast_node.h"
#include "array_node.h"
#include "lib/reglex.h"

class HashNode : public ASTNode{
public:
  HashNode(const std::string &id);
  ASTResult eval(RefEnv *env);
private:
  std::string _id;
};

#endif