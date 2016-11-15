#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>

class Symbol{
	public:
		union T {
			int n;
			char* s;
			float f;
		};
		enum Types { INT, STRING, FLOAT };
		enum Contexts {GLOBAL, LOCAL, PARAMETER};
		Symbol(std::string name, Types type, T value);
		Symbol(const Symbol& sym);
		~Symbol();
		std::string Name;
		Types Type;
		Contexts Context;
		T Value; // Maybe used for string

		// If its a local, need to have the local number
		int local_variable_number;

		// It its a parameter, needs to have the parameter number
		int parameter_number;

		// offset in the current stack frame.
		int offset;

};

#endif
