#ifndef _TABLE_H_
#define _TABLE_H_

#include "symbol.hpp"
#include <list>
#include <string>

class Table{
	public:
		Table(std::string _name);
		void InsertSymbol(Symbol sym);
		Symbol* GetSymbol(std::string name);
		void PrintSymbols();
	private:
		bool hasBeenPrinted;
		std::string name;
		std::list<Symbol> symbols;
};

#endif
