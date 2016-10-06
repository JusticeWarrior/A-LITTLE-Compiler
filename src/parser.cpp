#include "parser.hpp"

extern void yyparser(LittleParser& parser, LittleScanner& scanner);

LittleParser::LittleParser(std::istream* i, std::ostream* o):
  scanner(i,o),
  accept(true),
  error_message(0)
  {}

LittleParser::LittleParser(std::istream* i):
  scanner(i),
  accept(true)
  {}

LittleParser::~LittleParser(){
  // Cleanup str_arr_arr
  std::vector<std::vector<char*>* >::iterator str_arr_it;
  std::vector<char*>::iterator str_it;

  // Clean up sym_arr_arr
  std::vector<std::list<Symbol*>* >::iterator sym_arr_it;
  std::list<Symbol*>::iterator sym_it;

  // Iterate through all of the string vectors
  for (str_arr_it = str_arr_arr.begin(); str_arr_it != str_arr_arr.end(); str_arr_it++){
    // For each string vector, iterate through its strings and free them
    for (str_it = (**str_arr_it).begin(); str_it != (**str_arr_it).end(); str_it++){
      free(*str_it);
    }
    // now delete the array
    delete *str_arr_it;
  }

  // Iterate through all of the symbol vectors
  for (sym_arr_it = sym_arr_arr.begin(); sym_arr_it != sym_arr_arr.end(); sym_arr_it++){
    // For each symbol vector, iterate through its symbols and delete them
    for (sym_it = (**sym_arr_it).begin(); sym_it != (**sym_arr_it).end(); sym_it++){
      delete *sym_it;
    }
    // now delete the array
    delete *sym_arr_it;
  }
}

void LittleParser::error(const char* err){
  error_message = err;
  accept = false;
}

const char* LittleParser::get_error_message(){
  return error_message;
}

void LittleParser::register_str_arr(std::vector<char*>* arr){
  str_arr_arr.push_back(arr);
}

void LittleParser::register_sym_arr(std::list<Symbol*>* arr){
  sym_arr_arr.push_back(arr);
}

void LittleParser::parse(){
  yyparse(*this, scanner);
}

bool LittleParser::accepted(){
  return accept;
}
