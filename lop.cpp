#include <iostream>
#include <string>
#include <fstream>
#include "calculator_lexer.h"
#include "calculator_parser.h"
#include "ref_env.h"

int main(int argc, char* argv[]) {
  CalculatorParser parser;
  std::string input;
  RefEnv global;

  char* file_type = argv[1] + strlen(argv[1]) - 4;
  if(strcmp(file_type, ".lop") != 0){
    throw std::runtime_error("Invalid file type. Please ensure the file is of type .lop");
  }
  std::ifstream file(argv[1]);
  CalculatorLexer lexer(file);
  ASTNode *tree = parser.parse(&lexer);
  if(tree == nullptr) 
    return 0; 
  ASTResult result = tree->eval(&global);
  delete tree;
}