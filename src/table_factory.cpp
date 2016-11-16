#include "table_factory.hpp"
#include "stdlib.h"
#include "data_object.hpp"
#include "parser.hpp"
#include <sstream>
#include <iostream>

TableFactory::TableFactory():
  error(false),
  ss(new std::stringstream()),
  global_dec(new std::stringstream())
  {}
TableFactory::~TableFactory(){
  delete ss;
  delete global_dec;
}

bool TableFactory::insert_symbol(Symbol sym){
  if (scope_stack.front().GetSymbol(sym.Name)){
    ss->clear();
    ss->str("");
    *ss << "DECLARATION ERROR " << sym.Name << std::endl;
    return false;
  }
  else{
    if (scope_stack.size() > 1 && sym.Context == Symbol::GLOBAL) {
      std::cerr << "Finished local named " << sym.Name << std::endl;
      sym.Context = Symbol::LOCAL;
      sym.local_variable_number = DataObject::parser->current_function().get_next_local();
    }
      
    scope_stack.front().InsertSymbol(sym);
    return true;
  }
}

void TableFactory::push_table(std::string name){
  if (!scope_stack.empty()){ 
   scope_stack.front().PrintSymbols(ss);
   *ss << std::endl;
  }
  scope_stack.push_front(Table(name));
}

void TableFactory::pop_table(){
  scope_stack.front().PrintSymbols(ss);
  if (scope_stack.size() == 1)
    scope_stack.front().PrintDeclarations(global_dec);
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

void TableFactory::print_table_stack_trace(std::stringstream& ss_out) {
  ss_out << ss->rdbuf();
}

void TableFactory::print_global_declarations(std::stringstream& ss_out) {
  ss_out << global_dec->rdbuf();
}

