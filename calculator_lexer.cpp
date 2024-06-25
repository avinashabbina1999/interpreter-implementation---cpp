// File: calculator_lexer.cpp
// Purpose: This file contains the implementation of the calculator lexer.
// Author: Robert Lowe
#include "calculator_lexer.h"

CalculatorLexer::CalculatorLexer(std::istream &_is) : _is(_is), _first(true) {
  // set up the token definitions in the lexer
  _lex.add_token(SKIP, make_regex(" |\\n"));
  _lex.add_token(ADD, make_regex("\\+"));
  _lex.add_token(SUB, make_regex("-"));
  _lex.add_token(MUL, make_regex("\\*"));
  _lex.add_token(DIV, make_regex("/"));
  _lex.add_token(POW, make_regex("^"));
  _lex.add_token(LPAREN, make_regex("\\("));
  _lex.add_token(RPAREN, make_regex("\\)"));
  _lex.add_token(INT, make_regex("[0-9]+"));
  _lex.add_token(REAL, make_regex("[0-9]+\\.[0-9]+"));
  _lex.add_token(IF, make_regex("if"));
  _lex.add_token(THEN, make_regex("then"));
  _lex.add_token(STOP, make_regex("stop"));
  _lex.add_token(ACCESS, make_regex("_"));
  _lex.add_token(COLON, make_regex(":"));
  _lex.add_token(ASSIGN, make_regex(":="));
  _lex.add_token(SEMI, make_regex(";"));
  _lex.add_token(LBRACE, make_regex("{"));
  _lex.add_token(RBRACE, make_regex("}"));
  _lex.add_token(EQUAL, make_regex("="));
  _lex.add_token(COMMA, make_regex(","));
  _lex.add_token(FUNCTION, make_regex("function"));
  _lex.add_token(READ, make_regex("read"));
  _lex.add_token(DISPLAY, make_regex("display"));
  _lex.add_token(PROMPT, make_regex("prompt"));
  _lex.add_token(INPUT, make_regex("input"));
  _lex.add_token(CONSTRUCTOR, make_regex("constructor"));
  _lex.add_token(STRING, make_regex("\"[^\"]*\""));
  _lex.add_token(NEQ, make_regex("<>"));
  _lex.add_token(LT, make_regex("<"));
  _lex.add_token(LTE, make_regex("<="));
  _lex.add_token(GT, make_regex(">"));
  _lex.add_token(GTE, make_regex(">="));
  _lex.add_token(HASH, make_regex("#"));
  _lex.add_token(LSQ, make_regex("\\["));
  _lex.add_token(RSQ, make_regex("\\]"));
  _lex.add_token(PIPE, make_regex("\\|"));
  _lex.add_token(NEW, make_regex("new"));
  
  _lex.add_token(ID, make_regex("[a-zA-Z][a-zA-Z0-9]*"));

  // prime the lexer to retrieve a line.
  _tok.tok = EOL;
}

// Get the next token from the input string
Lexer::Token CalculatorLexer::next() {
  std::string line;

  do {
    if(_tok.tok == EOL) {
      std::getline(_is, line);
      _lex.input(line);
      if(not _is) { 
        _tok.tok = EOI; 
        return _tok;
      }
    }
    
    _tok = _lex.next();
  } while (_tok.tok == SKIP);

  if(_tok.tok == EOI) {
    _tok.tok = EOL;
  }

  return _tok;
}