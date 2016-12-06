#ifndef _OPERAND_H_
#define _OPERAND_H_

#include <string>

class Operand{
	public:
		enum Types { REGISTER, LITERAL, LABEL, VARIABLE, LOCAL, PARAMETER, RETURN, NOTHING, MAGIC_TYPE};
		enum DataTypes {FLOAT, INT};
		Operand();
		Operand(Types type, std::string value);
		Operand(Types type, int reg);
		std::string ToString();
		std::string ToAssemblyString();
		Types Type;
		Types AwfulType;
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
