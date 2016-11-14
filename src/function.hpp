#include <string>
#include <list>
#include "iri.hpp"

struct Function {
  Function(std::string asdf, int num_params);
  int num_params;
  std::string name;
  std::list<IRI*> iri_list;

  int get_next_temp();
  int get_next_local();
  
  private:
    int next_temp;
    int next_local;
};

// Types of symbols :
//  Functions (Pointer to function object)
//  Global variables (No other information)
//  Parameter (index in function)
//  Local variable (index in function)
//
//  Each symbol table stack frame has a number?
