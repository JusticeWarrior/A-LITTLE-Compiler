#ifndef _TABLE_FACTORY_H_
#define _TABLE_FACTORY_H_

#include "table.hpp"
#include <list>
#include <sstream>

class TableFactory{
  public:
    TableFactory();
    ~TableFactory();
    bool insert_symbol(Symbol sym);
    void push_table(std::string name);
    void pop_table();
    Symbol* get_symbol(std::string name);
    std::stringstream* ss;

  private:
    std::list<Table> scope_stack;
    bool error;
    
};

#endif
