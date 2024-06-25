#include "object_access_node.h"
#include <iostream>

ObjectAccessNode::ObjectAccessNode(const std::string &name):obj_name(name){}

void ObjectAccessNode::add_argument(ASTNode *arg){
  _args.push_back(arg);
}

void ObjectAccessNode::add_val(const std::string &var){
  _var = var;
}

void ObjectAccessNode::add_func(const std::string &func){
  _func = func;
  _var = "";
}

ASTResult ObjectAccessNode::eval(RefEnv* env){
  ASTResult* temp= env->lookup(obj_name);
  if(this->_var!=""){
    ObjectCreateNode *node = temp->value.obj;
    ASTResult *res = node->local->lookup(this->_var);
    return *res;
  }else{ 
    ClassNode* cls = temp->value.obj->class_node;
    std::vector<ASTResult> argResults;
    for(int i=0;i<this->_args.size();i++)
      argResults.push_back(this->_args[i]->eval(env));
    for(int i=0;i<cls->func().size();i++){
      FunctionNode *node = dynamic_cast<FunctionNode*>(cls->func()[i]);
      if(node->name() == this->_func){
        ASTResult result = node->call(temp->value.obj->local, argResults); 
        return result;
      }    
    }
    
  }
  return ASTResult();
}

