#ifndef _PARSER_H_
#define _PARSER_H_

#include "scanner.hpp"
#include "table_factory.hpp"

#include <iostream>
#include <vector>
class LittleParser;

extern int yyparse(LittleParser& parser, LittleScanner& scanner);

class LittleParser{
  public:
    LittleParser(std::istream* i, std::ostream* o);
    LittleParser(std::istream* i);
    ~LittleParser();
    void parse();
    void error(const char* error);
    bool accepted();
    const char* get_error_message();
    void register_str_arr(std::vector<char*>*);
    void register_sym_arr(std::list<Symbol*>*);
    TableFactory table_factory;
  private:
    bool accept;
    LittleScanner scanner;
    const char* error_message;
    std::vector<std::vector<char*>* > str_arr_arr;
    std::vector<std::list<Symbol*>* > sym_arr_arr;

};

#endif
