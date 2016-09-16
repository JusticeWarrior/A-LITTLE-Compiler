#include "parser.hpp"

extern void yyparser(LittleParser& parser, LittleScanner& scanner);

LittleParser::LittleParser(std::istream* i, std::ostream* o):
  scanner(i,o),
  accept(true)
  {}

LittleParser::LittleParser(std::istream* i):
  scanner(i),
  accept(true)
  {}

void LittleParser::error(const char* err){
  accept = false;
}

void LittleParser::parse(){
  yyparse(*this, scanner);
}

bool LittleParser::accepted(){
  return accept;
}
