#ifndef _TABLE_H_
#define _TABLE_H_

#include "symbol.hpp"
#include <list>
#include <string>
#include <sstream>

class Table{
	public:
		Table(std::string _name);
		void InsertSymbol(Symbol sym);
		Symbol* GetSymbol(std::string _name);
		void PrintSymbols(std::stringstream* stream);
	private:
		bool hasBeenPrinted;
		std::string name;
		std::list<Symbol> symbols;
};

#endif
