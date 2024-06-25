#include "array_assign_node.h"
#include "iostream"

ArrayAssignNode::ArrayAssignNode(const std::string &id, int ind, ASTNode *val):_id(id),_ind(ind),_val(val){}

ArrayAssignNode::ArrayAssignNode(const std::string &id, ASTNode *node, ASTNode *val):_id(id),_node(node),_val(val),_ind(0){}

ASTResult ArrayAssignNode::eval(RefEnv *env){
  ASTResult *node = env->lookup(_id);
  if(node == nullptr || node->type != ASTResult::ARR){
    throw std::runtime_error(this->_id + " is not an array");
  }
  ASTResult val = _val->eval(env);
  if(_ind > 0){
    node->value.arr->at(_ind-1) = val;
  }else{
    ASTResult temp = _val->eval(env);
    node->value.arr->at(_node->eval(env).value.i-1) = val;
  }
  return ASTResult();
}