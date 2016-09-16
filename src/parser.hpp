#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include "scanner.hpp"
class LittleParser;

extern int yyparse(LittleParser& parser, LittleScanner& scanner);

class LittleParser{
  public:
    LittleParser(): scanner(&std::cin, &std::cout){};
    void parse();
    void error(const char* error);
    bool accepted();
  private:
    bool accept;
    LittleScanner scanner;

};

#endif
