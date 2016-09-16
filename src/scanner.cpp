#include "scanner.hpp"

LittleScanner::LittleScanner(std::istream* i, std::ostream* o): yyFlexLexer(i,o){}

LittleScanner::LittleScanner(std::istream *i): yyFlexLexer(i, &nullStream){};

int NullBuff::overflow(int c) {return c;}

NullBuff nullBuff;

std::ostream nullStream(&nullBuff);
