#ifndef _TABLE_H_
#define _TABLE_H_

#include "symbol.hpp"
#include <list>
#include <string>

class Table{
	public:
		void InsertSymbol(Symbol sym);
		Symbol GetSymbol(std::string name);
		void PrintChildren();
		Table* Parent;
	private:
		std::list<Symbol> symbols;
		std::list<Table*> children;
};

#endif
