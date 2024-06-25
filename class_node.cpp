#include "class_node.h"

ClassNode::ClassNode(const std::string &name):_name(name){
  _func.clear();
  _var.clear();
}

void ClassNode::add_instance(const std::string &id) {
  this->_var.push_back(id);
}

void ClassNode::add_function(ASTNode *f){
  this->_func.push_back(f);
}

void ClassNode::add_constructor(ASTNode *c){
  this->_constructor = c;
}

ASTNode *ClassNode::get_constructor() {
  return this->_constructor;
}

std::vector<std::string> ClassNode::var(){
  return this->_var;
}

std::vector<ASTNode*> ClassNode::func(){
  return this->_func;
}


ASTResult ClassNode::eval(RefEnv *env){
  ASTResult result;

  // build the result
  result.type = ASTResult::CLASS;
  result.value.cls = this;

  // enter ourselves in the environment
  env->declare(_name);
  *(env->lookup(_name)) = result;

  return result;
}