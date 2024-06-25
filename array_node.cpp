#include "array_node.h"


void ArrayNode::add_element(ASTNode *node){
  _param.push_back(node);
}

ASTResult ArrayNode::eval(RefEnv *env) {
  ASTResult result;

  // build the result
  result.type = ASTResult::ARR;
  result.value.arr = new std::vector<ASTResult>();
  for(auto par : _param) {
    result.value.arr->push_back(par->eval(env));
  }
  return result;
}
