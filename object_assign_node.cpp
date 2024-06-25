#include "object_assign_node.h"
#include "iostream"

ObjectAssignNode::ObjectAssignNode(const std::string &obj):obj_name(obj){}

void ObjectAssignNode::add_var(const std::string &var){
  this->_var = var;
}

void ObjectAssignNode::add_val(ASTNode *val){
  this->_val = val;
}

ASTResult ObjectAssignNode::eval(RefEnv* env){
  ASTResult* obj = env->lookup(obj_name);
  RefEnv *local = obj->value.obj->local;
  ASTResult *result = local->lookup(this->_var);
  if(!result){
    local->declare(this->_var);
    result = local->lookup(this->_var);
  }
  *result = this->_val->eval(env);
  return *result;
}
