#ifndef OBJECT_ASSIGN_NODE_H
#define OBJECT_ASSIGN_NODE_H

#include "ast_node.h"
#include "object_create_node.h"

class ObjectAssignNode: public ASTNode{
public:
  ObjectAssignNode(const std::string &obj);
  virtual void add_var(const std::string &var);
  virtual void add_val(ASTNode *val);
  virtual ASTResult eval(RefEnv* env);
private:
  std::string obj_name;
  std::string _var;
  ASTNode* _val;
};

#endif