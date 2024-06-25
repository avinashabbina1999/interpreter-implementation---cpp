#include "access_node.h"
#include <stdexcept>
#include <iostream>


AccessNode::AccessNode(const std::string &id,int ind):_id(id),_ind(ind){}

AccessNode::AccessNode(const std::string &id,ASTNode *node):_id(id),_node(node),_ind(0){}


ASTResult AccessNode::eval(RefEnv *env) {
  ASTResult res;
  std::stringstream stream;
  ASTResult *node = env->lookup(_id);
  if(node == nullptr){
    throw std::runtime_error(this->_id + " is not an array/string");
  }
  if(node->type == ASTResult::ARR){
    std::vector<ASTResult> temp = *node->value.arr;
    if(_ind > 0 && _ind <= node->value.arr->size()){
      res = temp[_ind-1];
    } else {
      res = temp[_node->eval(env).value.i-1];
    }
    
  } else if(node->type == ASTResult::STR) {
    if(_ind > 0 && _ind <= node->value.sptr->size()){
      stream << node->value.sptr->at(_ind-1);
    } else {
      stream << node->value.sptr->at(_node->eval(env).value.i-1);
    }
    
    int integer;
    double real;
    if(stream >> integer){
      res.type = ASTResult::INT;
      res.value.i = std::stoi(stream.str());
    }else if(stream >> real){
      res.type = ASTResult::REAL;
      res.value.r = std::stod(stream.str());
    }else{
      res.type = ASTResult::STR;
      res.value.sptr = new std::string(stream.str());
    }
  }  
  return res;
}
