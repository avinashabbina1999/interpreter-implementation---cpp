#include "hash_node.h"
#include <stdexcept>

HashNode::HashNode(const std::string &id):_id(id){}

ASTResult HashNode::eval(RefEnv *env) {
  ASTResult res;
  res.type = ASTResult::INT;

  ASTResult *node = env->lookup(_id);
  if(node == nullptr){
    throw std::runtime_error(this->_id + " is not an array/string");
  }

  if(node->type == ASTResult::ARR){
    std::vector<ASTResult> temp = *node->value.arr;
    res.value.i = temp.size();
  }else if(node->type == ASTResult::STR){
    res.value.i = node->value.sptr->size();
  }else{
    throw std::runtime_error(this->_id + " is not an array/string");
  }
  return res;
}