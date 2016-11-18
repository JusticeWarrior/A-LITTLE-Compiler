#include "table.hpp"

Table::Table(std::string _name)
	:name(_name),
	hasBeenPrinted(false)
	{ }

void Table::InsertSymbol(Symbol sym) {
	symbols.push_back(sym);
}

Symbol* Table::GetSymbol(std::string _name) {
	std::list<Symbol>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++) {
		if (it->Name == _name) {
			return &(*it);
		}
	}
	return NULL;
}

void Table::PrintSymbols(std::stringstream* stream) {	
	if (hasBeenPrinted)
		return;

	*stream << "Symbol table " << name << std::endl;

	std::list<Symbol>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++) {
		std::string enumStr;
		if (it->Type == Symbol::INT)
			enumStr = "INT";
		else if (it->Type == Symbol::STRING)
			enumStr = std::string("STRING value ") + it->Value.s;
		else
			enumStr = "FLOAT";
		*stream << "name " << it->Name << " type " << enumStr << std::endl;
	}

	//*stream << std::endl;

	hasBeenPrinted = true;
}


void Table::PrintDeclarations(std::stringstream* stream) { 
  std::list<Symbol>::iterator it;
  for (it = symbols.begin(); it != symbols.end(); it++) {
    if ((*it).Context == Symbol::FUNCTION)
      continue;
    if ((*it).Type == Symbol::STRING)
      *stream << "str " <<  (*it).Name << " " << (*it).Value.s <<  std::endl;
    else
      *stream << "var " << (*it).Name << std::endl;
  }
}
