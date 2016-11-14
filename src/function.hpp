

struct Function {
  std::string name;
  int num_parameters;
  int num_locals;
  std::list<IRI*> iri_list;

};

// Types of symbols :
//  Functions (Pointer to function object)
//  Global variables (No other information)
//  Parameter (index in function)
//  Local variable (index in function)
//
//  Each symbol table stack frame has a number?
