#include "table_factory.hpp"
#include "stdlib.h"

TableFactory::TableFactory(){}

void TableFactory::insert_symbol(Symbol sym){
  scope_stack.front().InsertSymbol(sym);
}

void TableFactory::push_table(std::string name){
  if (!scope_stack.empty()){
    scope_stack.front().PrintSymbols();
  }
  scope_stack.push_front(Table(name));
}

void TableFactory::pop_table(){
  scope_stack.front().PrintSymbols();
  scope_stack.pop_front();
}

Symbol* TableFactory::get_symbol(std::string name){
  std::list<Table>::iterator it = scope_stack.begin();
  Symbol* sym = NULL;
  while (it != scope_stack.end() && sym == NULL){
    sym = (*it).GetSymbol(name);
    it++;
  }
  return sym;
}

