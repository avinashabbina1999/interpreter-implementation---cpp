#ifndef CLASS_NODE_H
#define CLASS_NODE_H

#include "ast_node.h"
#include "lib/reglex.h"
#include "function_node.h"
#include "ref_node.h"
#include <vector>

class ClassNode : public ASTNode{
public:
  ClassNode(const std::string &name);
  virtual void add_instance(const std::string &id);
  virtual void add_function(ASTNode *f);
  virtual void add_constructor(ASTNode *c);
  virtual ASTNode* get_constructor();
  virtual std::vector<std::string> var();
  virtual std::vector<ASTNode*> func();
  virtual ASTResult eval(RefEnv *env);
private:
  std::string _name;
  std::vector<std::string> _var;
  std::vector<ASTNode*> _func;
  ASTNode* _constructor;
};

#endif