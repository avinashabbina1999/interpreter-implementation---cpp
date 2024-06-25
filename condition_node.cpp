#include "condition_node.h"


ConditionNode::ConditionNode(const std::string &cond):_cond(cond){}

ASTResult ConditionNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  ASTResult result;
  result.type = ASTResult::INT;

  double lhs_real,rhs_real;
  std::string lhs_str,rhs_str;


  if(lhs.type == ASTResult::INT)
    lhs_real = lhs.value.i * 1.0;
  else if(lhs.type == ASTResult::REAL)
    lhs_real = lhs.value.r;
  else if(lhs.type == ASTResult::STR)
    lhs_str = *lhs.value.sptr;

  if(rhs.type == ASTResult::INT)
    rhs_real = rhs.value.i * 1.0;
  else if(rhs.type == ASTResult::REAL)
    rhs_real = rhs.value.r;
  else if(rhs.type == ASTResult::STR)
    rhs_str = *rhs.value.sptr;
    

  if(_cond == "="){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);     
      result.value.i = lhs_str==rhs_str;
    }else{
      result.value.i = lhs_real==rhs_real?1:0;
    }
  }else if(_cond == "<>"){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);
      result.value.i = lhs_str!=rhs_str?1:0;
    }else{
      result.value.i = lhs_real!=rhs_real?1:0;
    }
  }else if(_cond == "<="){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);
      result.value.i = lhs_str<=rhs_str?1:0;
    }else{
      result.value.i = lhs_real<=rhs_real?1:0;
    }
  }else if(_cond == "<"){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);
      result.value.i = lhs_str<rhs_str?1:0;
    }else{
      result.value.i = lhs_real<rhs_real?1:0;
    }
  }else if(_cond == ">="){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);
      result.value.i = lhs_str>=rhs_str?1:0;
    }else{
      result.value.i = lhs_real>=rhs_real?1:0;
    }
  }else if(_cond == ">"){
    if(!lhs_str.empty() || !rhs_str.empty()){
      if(lhs_str.empty())
        lhs_str = std::to_string(lhs_real);
      if(rhs_str.empty())
        rhs_str = std::to_string(rhs_real);
      result.value.i = lhs_str>rhs_str?1:0;
    }else{
      result.value.i = lhs_real>rhs_real?1:0;
    }
  }
    
    
  return result;
}