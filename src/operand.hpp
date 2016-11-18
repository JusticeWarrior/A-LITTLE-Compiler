#ifndef _OPERAND_H_
#define _OPERAND_H_

#include <string>

class Operand{
	public:
		enum Types { REGISTER, LITERAL, LABEL, VARIABLE, LOCAL, PARAMETER, RETURN};
		enum DataTypes {FLOAT, INT};
		Operand(Types type, std::string value);
		Operand(Types type, int reg);
		std::string ToString();
		std::string ToAssemblyString();
		Types Type;
		DataTypes DataType;
		std::string Value;
		int Reg;    // IRI code
		int Offset; // assembly code for LOCAL and PARAMETER types
		
};

#endif

/*
$L3  ->  $-15
$P2  ->  $-2
*/
