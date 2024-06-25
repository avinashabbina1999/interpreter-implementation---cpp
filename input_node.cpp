#include "input_node.h"

InputNode::InputNode(const std::string &input,const std::string &id){
  _input = input;
  _id = id;
}

InputNode::InputNode(const std::string &id){
  _id = id;
}

ASTResult InputNode::eval(RefEnv *env){
  if(!_input.empty()){
    std::cout<<_input<<" ";
  }else{
    //std::cout<<_id<<"=";
  }
  std::string input;
  std::getline(std::cin,input);
  if(!input.empty()){
    env->declare(_id);
    ASTResult *res = env->lookup(_id);
    std::stringstream stream;
    stream << input;
    int integer;
    double real;
    if(stream >> integer){
      res->type = ASTResult::INT;
      res->value.i = std::stoi(input);
    }else if(stream >> real){
      res->type = ASTResult::REAL;
      res->value.r = std::stod(input);
    }else{
      res->type = ASTResult::STR;
      res->value.sptr = new std::string(input);
    }
  }else{
    throw std::runtime_error("input required");
  }
  return ASTResult();
}