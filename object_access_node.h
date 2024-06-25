#ifndef OBJECT_ACCESS_NODE_H
#define OBJECT_ACCESS_NODE_H

#include "ast_node.h"
#include "object_create_node.h"
#include "function_node.h"
#include <vector>


class ObjectAccessNode: public ASTNode{
public:
  ObjectAccessNode(const std::string &name); 
  virtual void add_argument(ASTNode *arg);
  virtual void add_val(const std::string &var);
  virtual void add_func(const std::string &func);
  virtual ASTResult eval(RefEnv* env);
private:
  std::string obj_name;
  std::string _func;
  std::string _var;
  std::vector<ASTNode*> _args; 
};

#endif