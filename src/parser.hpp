#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include "scanner.hpp"
#include "table_factory.hpp"
class LittleParser;

extern int yyparse(LittleParser& parser, LittleScanner& scanner);

class LittleParser{
  public:
    LittleParser(std::istream* i, std::ostream* o);
    LittleParser(std::istream* i);
    void parse();
    void error(const char* error);
    bool accepted();
  private:
    bool accept;
    LittleScanner scanner;
    TableFactory table_factory;

};

#endif
