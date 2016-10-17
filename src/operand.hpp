#ifndef _OPERAND_H_
#define _OPERAND_H_

#include <string>

class Operand{
	public:
		enum Types { REGISTER, INTLITERAL, STRINGLITERAL, FLOATLITERAL, LABEL };
		Operand(Types type, std::string value);
		Operand(Types type, int reg);
		std::string ToString();
		std::string ToAssemblyString();
		Types Type;
		std::string Value;
		int Reg;
};

#endif
