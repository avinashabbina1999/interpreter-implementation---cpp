#include "string_node.h"

StringNode::StringNode(const std::string &input) {
  _input = input;
}

ASTResult StringNode::eval(RefEnv *env){
  ASTResult result;
  result.type = ASTResult::STR;
  result.value.sptr = new std::string(this->get_string());
  return result;
}

std::string StringNode::get_string() const{
  std::string input = this->_input.substr(1,this->_input.length()-2);
  std::string output;
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] == '\\' && i + 1 < input.size()) {
        switch (input[i + 1]) {
            case 'n':
                output += '\n';
                break;
            case 't':
                output += '\t';
                break;
            case 'r':
                output += '\r';
                break;
            case 'b':
                output += '\b';
                break;
            case 'f':
                output += '\f';
                break;
            case '\\':
                output += '\\';
                break;
            case '\"':
                output += '\"';
                break;
            case '\'':
                output += '\'';
                break;
            case 'a':
                output += '\a';
                break;
            case 'v':
                output += '\v';
                break;
            default:
                // If it's not a recognized escape sequence, leave it as is
                output += input[i];
                output += input[i + 1];
                break;
        }
        ++i; // Skip the next character since it's part of an escape sequence
    } else {
        output += input[i];
    }
  }
  return output;
}