#ifndef _OPERAND_H_
#define _OPERAND_H_

#include <string>

class Operand{
	public:
		enum Types { REGISTER, LITERAL, LABEL, VARIABLE, LOCAL, PARAMETER, RETURN, NOTHING};
		enum DataTypes {FLOAT, INT};
		Operand();
		Operand(Types type, std::string value);
		Operand(Types type, int reg);
		std::string ToString();
		std::string ToAssemblyString();
		Types Type;
		DataTypes DataType;
		std::string Value;
		int Reg;    // IRI code
		int Offset; // assembly code for LOCAL and PARAMETER types
		int Awful;
		
};

#endif

/*
$L3  ->  $-15
$P2  ->  $-2
*/
