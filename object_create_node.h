#ifndef OBJECT_CREATE_NODE_H
#define OBJECT_CREATE_NODE_H

#include "ast_node.h"
#include "class_node.h"
#include <stdexcept>

class ObjectCreateNode : public ASTNode{
public:
  ObjectCreateNode(const std::string &cls);
  virtual void add_argument(ASTNode *arg);
  ASTResult eval(RefEnv *env);
  RefEnv *local;
  ClassNode *class_node;
private:
  ASTResult res;
  std::string cls_name;
  std::vector<ASTNode* > _args;
};

#endif