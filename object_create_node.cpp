#include "object_create_node.h"
#include <iostream>

ObjectCreateNode::ObjectCreateNode(const std::string &cls) : cls_name(cls){
  this->res = ASTResult();
  this->class_node = nullptr;
  this->_args.clear();
}

void ObjectCreateNode::add_argument(ASTNode *arg){
  _args.push_back(arg);
}

ASTResult ObjectCreateNode::eval(RefEnv *env){
  res.type = ASTResult::OBJECT; 
  local = new RefEnv(env);
  class_node = env->lookup(cls_name)->value.cls;
  local->declare("my");
  res.value.obj = this;
  *(local->lookup("my")) = res;
  std::vector<std::string> instances = class_node->var();
  for(int i=0; i<instances.size(); i++) {
    local->declare(instances[i]);
  }
  std::vector<ASTResult> argResults;
  for(auto arg : _args)
    argResults.push_back(arg->eval(env));
  FunctionNode *constructor = dynamic_cast<FunctionNode*>(class_node->get_constructor());
  if(constructor == nullptr)
    throw std::runtime_error("Constructor not implemented");
  constructor->call(local, argResults);
  return res;
}