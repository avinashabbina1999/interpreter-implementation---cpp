// File: ast_node.cpp
// Purpose: Empty virtual destructor for ASTNode.
#include "ast_node.h"
#include "array_node.h"

// implement our language's truthiness
bool ASTResult::is_true() const {
  int result;
  
  // extract an integer for the result
  switch(type) {
    case INT:
      result = value.i;
      break;
    case REAL:
      result = (int) value.r;
      break;
    case STR:
      result = value.sptr->size();
      break;
    case ARR:
      result = value.arr->size();
      break;
    case VOID:
      result = 0;
      break;
  }

  return result != 0;
}

ASTNode::~ASTNode() { }