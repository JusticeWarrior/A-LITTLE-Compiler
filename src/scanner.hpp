#ifndef _SCANNER_H_
#define _SCANNER_H_

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include <iostream>
#include "tokens.hpp"

class NullBuff : public std::streambuf{
  public:
    virtual int overflow(int c);
};
extern std::ostream nullStream;


class LittleScanner: public yyFlexLexer{
  public:
    LittleScanner(std::istream* i, std::ostream* o);
    LittleScanner(std::istream* i);
    virtual int yylex();
  private:
};

#endif
