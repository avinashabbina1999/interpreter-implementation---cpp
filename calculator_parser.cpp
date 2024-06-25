// File: calculator_parser.cpp
// Purpose: This file contains the implementation of the calculator parser.

#include "calculator_parser.h"
#include "add_node.h"
#include "assign_node.h"
#include "divide_node.h"
#include "equal_node.h"
#include "function_call_node.h"
#include "function_node.h"
#include "if_node.h"
#include "loop_node.h"
#include "multiply_node.h"
#include "number_node.h"
#include "pow_node.h"
#include "ref_node.h"
#include "statements_node.h"
#include "stop_node.h"
#include "subtract_node.h"
#include "string_node.h"
#include "display_node.h"
#include "input_node.h"
#include "condition_node.h"
#include "array_node.h"
#include "access_node.h"
#include "hash_node.h"
#include "array_assign_node.h"
#include "class_node.h"
#include "object_create_node.h"
#include "object_assign_node.h"
#include "object_access_node.h"
#include <stdexcept>

// advance the lexer
void CalculatorParser::next() { _cur = _lexer->next(); }

// check to see if the current token matches the given token
bool CalculatorParser::has(int t) { return _cur.tok == t; }

// < Expression > ::= < Ref > < Expression' >
//                    | < If >
//                    | < Stop >
//                    | < Sum >
//                    | < Loop >
//                    | < Function >
ASTNode *CalculatorParser::parse_expression() {
  if (has(CalculatorLexer::ID)) {
    ASTNode *left = parse_ref();
    return parse_expression2(left);
  } else if (has(CalculatorLexer::IF)) {
    return parse_if();
  } else if (has(CalculatorLexer::STOP)) {
    next();
    return new StopNode();
  } else if (has(CalculatorLexer::LBRACE)) {
    return parse_loop();
  } else if (has(CalculatorLexer::FUNCTION)) {
    return parse_function();
  } else if (has(CalculatorLexer::DISPLAY)) {
    return parse_display();
  } else if (has(CalculatorLexer::INPUT) || has(CalculatorLexer::PROMPT) || has(CalculatorLexer::READ)) {
    return parse_prompt();
  } else if (has(CalculatorLexer::LT)) {
    return parse_array();
  } 
  // else if (has(CalculatorLexer::NEW)) {
  //   return parse_object_create();
  // }

  return parse_sum();
}

// < Expression' > ::= ASSIGN < Expression >
//                     | < Sum' >
ASTNode *CalculatorParser::parse_expression2(ASTNode *left) {
  if (has(CalculatorLexer::ASSIGN)) {
    next();
    AssignNode *node = new AssignNode();
    node->left(left);
    node->right(parse_expression());
    return node;
  }

  if(has(CalculatorLexer::MUL) || has(CalculatorLexer::DIV))
    return parse_term2(left);
  else if(has(CalculatorLexer::POW))
    return parse_factor2(left);
  return parse_sum2(left);
}

// < Sum > ::= < Term > < Sum’ >
ASTNode *CalculatorParser::parse_sum() {
  ASTNode *node = parse_term();
  return parse_sum2(node);
}

// < Sum' > ::= ADD <Term> <Sum'>
//                   | SUB <Term> <Sum'>
//                   | EQUAL < Term > < Sum' >
//                   | ""
ASTNode *CalculatorParser::parse_sum2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::ADD)) {
    next(); // consume ADD
    result = new AddNode();
  } else if (has(CalculatorLexer::SUB)) {
    next(); // consume SUB
    result = new SubtractNode();
  } else if (has(CalculatorLexer::EQUAL)) {
    next(); // consume EQUAL
    result = new EqualNode();
  }

  if (result) {
    result->left(left);
    result->right(parse_term());
    return parse_sum2(result);
  }

  return left; // epsilon
}

// <Term> ::= <Factor> <Term'>
ASTNode *CalculatorParser::parse_term() {
  ASTNode *node = parse_factor();
  return parse_term2(node);
}

// <Term'> ::= MUL <Factor> <Term'>
//             | DIV <Factor> <Term'>
//             | ""
ASTNode *CalculatorParser::parse_term2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::MUL)) {
    next(); // consume MUL
    result = new MultiplyNode();
  } else if (has(CalculatorLexer::DIV)) {
    next(); // consume DIV
    result = new DivideNode();
  }

  if (result) {
    result->left(left);
    result->right(parse_term());
    return parse_term2(result);
  }

  return left; // epsilon
}

// <Factor> ::= <Exponent> <Factor'>
ASTNode *CalculatorParser::parse_factor() {
  ASTNode *node = parse_exponent();
  return parse_factor2(node);
}

// <Factor'> ::= POW <Exponent>
//               | ""
ASTNode *CalculatorParser::parse_factor2(ASTNode *left) {
  if (has(CalculatorLexer::POW)) {
    next(); // consume POW
    PowNode *node = new PowNode();
    node->left(left);
    node->right(parse_exponent());
    return parse_factor2(node);
  }

  return left; // epsilon
}

// <Exponent> ::= INT
//                | REAL
//                | LPAR <Expression> RPAR
//                | < Ref >
ASTNode *CalculatorParser::parse_exponent() {
  if (has(CalculatorLexer::INT) || has(CalculatorLexer::REAL)) {
    ASTNode *node = new NumberNode(_cur);
    next();
    return node;
  } else if(has(CalculatorLexer::STRING)) {
    ASTNode *node = new StringNode(_cur.lexeme);
    next();
    return node;
  } else if (has(CalculatorLexer::LPAREN)) {
    next(); // consume LPAR
    ASTNode *node = parse_expression();
    if (!has(CalculatorLexer::RPAREN)) {
      throw std::runtime_error("Expected ')'");
    }
    next(); // consume RPAR
    return node;
  } else if (has(CalculatorLexer::HASH)) {
    next(); // consume HASH
    ASTNode *node = new HashNode(_cur.lexeme);
    next();
    return node;
  } else if (has(CalculatorLexer::NEW)) {
    return parse_object_create();
  } else {
    return parse_ref();
  }
}

//< Ref >        ::= ID
//                   | ID ( args )
ASTNode *CalculatorParser::parse_ref() {
  // detect an error
  if (!has(CalculatorLexer::ID)) {
    throw std::runtime_error("Expected ID");
  }
  std::string id = _cur.lexeme;
  next();

  if (has(CalculatorLexer::ACCESS)) {
    next(); // consume ACCESS

    if (has(CalculatorLexer::ID)){
      RefNode *temp = new RefNode(_cur.lexeme);
      AccessNode *node = new AccessNode(id, temp);
      next();
      if (has(CalculatorLexer::ASSIGN)) {
        next(); // consume ASSIGN
        ArrayAssignNode *array_assign_node = new ArrayAssignNode(id, temp, parse_expression());
        return array_assign_node;
      }
      return node;
    } else if (has(CalculatorLexer::INT)){
      int ind = std::stoi(_cur.lexeme);
      AccessNode *node = new AccessNode(id, ind);
      next();
      if (has(CalculatorLexer::ASSIGN)) {
        next(); // consume ASSIGN
        ArrayAssignNode *array_assign_node = new ArrayAssignNode(id,ind, parse_expression());
        return array_assign_node;
      }
      return node;
    }else {
      throw std::runtime_error("Expected a valid index");
    }
    
  }

  if (has(CalculatorLexer::COLON)) {
    next(); // consume COLON
    if (has(CalculatorLexer::LSQ)) {
      return parse_class(id);
    } else if (has(CalculatorLexer::ID)) {
      return parse_object_access(id);
    }
  }

  if (!has(CalculatorLexer::LPAREN)) {
    return new RefNode(id);
  }
  return parse_function_call(id);
}

ASTNode *CalculatorParser::parse(CalculatorLexer *lexer) {
  // initialize the lexer
  _lexer = lexer;
  next();

  ASTNode *result = parse_statements();
  if (_cur.tok != CalculatorLexer::EOI && _cur.tok != CalculatorLexer::EOL) {
    throw std::runtime_error("Unexpected tokens at the end of expression");
  }

  return result;
}

ASTNode *CalculatorParser::parse_if_statement(){
  BinopNode *result = nullptr;

  if(has(CalculatorLexer::ID)){
    ASTNode *left = parse_ref();
    return parse_condition(left);
  } else if(has(CalculatorLexer::LT)) {
    return parse_array();
  }
  return parse_sum();
}

ASTNode *CalculatorParser::parse_condition(ASTNode *left){
  if(!has(CalculatorLexer::EQUAL) && !has(CalculatorLexer::NEQ) && !has(CalculatorLexer::LT) && !has(CalculatorLexer::LTE) && !has(CalculatorLexer::GT) && !has(CalculatorLexer::GTE)){
    return left;
  }
  BinopNode *result = new ConditionNode(_cur.lexeme);
  next();
  result->left(left);
  result->right(parse_term());
  return parse_condition(result);
}

// if condition then statement
ASTNode *CalculatorParser::parse_if() {
  if (has(CalculatorLexer::IF)) {
    next(); // consume IF
  } else {
    throw std::runtime_error("Expected IF");
  }

  ASTNode *cond = parse_if_statement();

  if (has(CalculatorLexer::THEN)) {
    next(); // consume THEN
  } else {
    throw std::runtime_error("Expected THEN");
  }

  ASTNode *then = parse_expression();

  IfNode *node = new IfNode();
  node->left(cond);
  node->right(then);

  return node;
}

// collection of statements
ASTNode *CalculatorParser::parse_statements() {
  bool consume = false;
  StatementsNode *node = new StatementsNode();
  while(true){
    if(consume) 
      next();
    
    while(has(CalculatorLexer::EOL))
      next();

    if(has(CalculatorLexer::RBRACE) || _cur.tok < 0)
      break;

    node->add_statement(parse_expression());
    
    consume = true;
    
    if(_cur.tok < 0)
      break; 
  }

  return node;
}

// a loop consisting of { statements }
ASTNode *CalculatorParser::parse_loop() {
  if (has(CalculatorLexer::LBRACE)) {
    next();
  } else {
    throw std::runtime_error("Expected {");
  }

  StatementsNode *body = (StatementsNode *)parse_statements();

  if (has(CalculatorLexer::RBRACE)) {
    next();
  } else {
    throw std::runtime_error("Expected }");
  }

  // build the loop node
  LoopNode *node = new LoopNode();
  node->body(body);
  return node;
}

// a function definition
ASTNode *CalculatorParser::parse_function() {
  std::string name;

  if (has(CalculatorLexer::FUNCTION)) {
    next(); // consume FUNCTION
  } else if (has(CalculatorLexer::CONSTRUCTOR)){
  } else {
    throw std::runtime_error("Expected FUNCTION");
  }

  if (has(CalculatorLexer::ID) || has(CalculatorLexer::CONSTRUCTOR)) {
    name = _cur.lexeme;
    next();
  } else {
    throw std::runtime_error("Expected ID");
  }

  // create the function
  FunctionNode *fun = new FunctionNode();
  fun->name(name);

  if (has(CalculatorLexer::LPAREN)) {
    next(); // consume LPAREN
  } else {
    throw std::runtime_error("Expected (");
  }

  // add the parameters
  while (has(CalculatorLexer::ID)) {
    fun->add_parameter(_cur.lexeme);
    next();
    if(has(CalculatorLexer::COMMA)){
      next();
    }
  }

  if (has(CalculatorLexer::RPAREN)) {
    next(); // consume RPAREN
  } else {
    throw std::runtime_error("Expected )");
  }

  // the function body is a loop
  fun->body(parse_loop());

  return fun;
}

ASTNode *CalculatorParser::parse_function_call(const std::string &id) {
  if (has(CalculatorLexer::LPAREN)) {
    next(); // consume LPAREN
  } else {
    throw std::runtime_error("Expected (");
  }

  FunctionCallNode *node = new FunctionCallNode();
  node->name(id);
  while (!has(CalculatorLexer::RPAREN)) {
    node->add_argument(parse_expression());
    if (has(CalculatorLexer::COMMA)) {
      next();
    }
  }

  if (has(CalculatorLexer::RPAREN)) {
    next(); // consume LPAREN
  } else {
    delete node;
    throw std::runtime_error("Expected (");
  }

  return node;
}

ASTNode *CalculatorParser::parse_display(){
  if(!has(CalculatorLexer::DISPLAY)){
    throw std::runtime_error("Expected display");
  }
  next();
  if(has(CalculatorLexer::STRING)){
    StringNode *node = new StringNode(_cur.lexeme);
    next();
    DisplayNode *display = new DisplayNode(node->get_string());
    return display;
  }else{
    DisplayNode *display = new DisplayNode(parse_expression());
    return display;
  }
}

ASTNode *CalculatorParser::parse_prompt(){
  if(!has(CalculatorLexer::INPUT) && !has(CalculatorLexer::PROMPT) && !has(CalculatorLexer::READ)){
    throw std::runtime_error("Expected input/prompt/read");
  }
  next();
  if(has(CalculatorLexer::STRING)){
    StringNode *node = new StringNode(_cur.lexeme);
    while(!has(CalculatorLexer::ID)){
      next();
    }
    InputNode *input = new InputNode(node->get_string(),_cur.lexeme);
    return input;
  }else{
    InputNode *input = new InputNode(_cur.lexeme);
    next();
    return input;
  }
}

ASTNode *CalculatorParser::parse_array(){
  if(!has(CalculatorLexer::LT)){
    throw std::runtime_error("Expected <");
  }
  next();
  
  ArrayNode *node = new ArrayNode();
  while(!has(CalculatorLexer::GT)){
    node->add_element(parse_expression());
  }
  next();
  return node;
}

ASTNode *CalculatorParser::parse_class(const std::string &id){
  if(!has(CalculatorLexer::LSQ)){
    throw std::runtime_error("Expected [");
  }
  next();
  ClassNode *node = new ClassNode(id);
  
  while(!has(CalculatorLexer::PIPE))
    next();
  next();
  while(!has(CalculatorLexer::PIPE)){
    node->add_instance(_cur.lexeme);
    next();
  }

  
  while(!has(CalculatorLexer::CONSTRUCTOR))
    next();
  node->add_constructor(parse_function());
  next();

  while(!has(CalculatorLexer::FUNCTION) && !has(CalculatorLexer::RSQ))
    next();
  
  if(has(CalculatorLexer::FUNCTION)){
    while(!has(CalculatorLexer::RSQ)){
      node->add_function(parse_function());
      while(!has(CalculatorLexer::FUNCTION) && !has(CalculatorLexer::RSQ))
        next();
    }
  }
  next();
  return node;
}

ASTNode *CalculatorParser::parse_object_create(){
  if(!has(CalculatorLexer::NEW)){
    throw std::runtime_error("Expected new");
  }
  next();

  if(!has(CalculatorLexer::ID)){
    throw std::runtime_error("Expected ID");
  }

  ObjectCreateNode *node = new ObjectCreateNode(_cur.lexeme);
  next();

  if(!has(CalculatorLexer::LPAREN)){
    throw std::runtime_error("Expected (");
  }
  next();

  while(!has(CalculatorLexer::RPAREN)){
    node->add_argument(parse_expression());
    if(has(CalculatorLexer::COMMA))
      next();
  }
  next();
  
  return node;
}

ASTNode *CalculatorParser::parse_object_access(const std::string &id){
  if(!has(CalculatorLexer::ID)){
    throw std::runtime_error("Expected ID");
  }

  ObjectAccessNode *node = new ObjectAccessNode(id);
  std::string _temp = _cur.lexeme;
  next();
  if(has(CalculatorLexer::LPAREN)){
    node->add_func(_temp);
    next();
    while(!has(CalculatorLexer::RPAREN)){
      node->add_argument(parse_expression());
      if(has(CalculatorLexer::COMMA))
        next();
    }   
    next();
  } else if (has(CalculatorLexer::ASSIGN)){
    next();
    ObjectAssignNode *obj = new ObjectAssignNode(id);
    obj->add_var(_temp);
    obj->add_val(parse_expression());
    return obj;
  } else {
    node->add_val(_temp);
  }
  return node;
}