#include "display_node.h"

DisplayNode::DisplayNode(const std::string &input) {
  _input = input;
}

DisplayNode::DisplayNode(ASTNode *node) {
  _node = node;
}

ASTResult DisplayNode::eval(RefEnv *env){
  if(!_input.empty()){
    std::cout<<_input;
  }else{
    ASTResult res = _node->eval(env);
    if(res.type == ASTResult::INT){
      std::cout<<res.value.i<<std::endl;
    }else if(res.type == ASTResult::REAL){
      std::cout<<res.value.r<<std::endl;
    }else if(res.type == ASTResult::STR){
      std::cout<<*res.value.sptr;
    }
  }
  return ASTResult();
}