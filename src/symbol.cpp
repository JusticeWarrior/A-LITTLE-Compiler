#include "symbol.hpp"
#include "string.h"

Symbol::Symbol(std::string name, Types type, T value)
	:Name(name), Type(type), Value(value), Context(GLOBAL){ }
Symbol::Symbol(const Symbol& sym)
  : Name(sym.Name),
    Type(sym.Type),
    Value(sym.Value),
    Context(sym.Context),
    local_variable_number(sym.local_variable_number),
    parameter_number(sym.parameter_number),
    offset(sym.offset)

{
  if (Type==STRING)
    Value.s = strdup(Value.s);
}

Symbol::~Symbol(){
  if (Type==STRING)
    free(Value.s);
}
