#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include <iostream>
#include "tokens.hpp"

class LittleScanner: public yyFlexLexer{
  public:
    LittleScanner(std::istream* i, std::ostream* o): yyFlexLexer(i,o){}
    virtual int yylex();
};
