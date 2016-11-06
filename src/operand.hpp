#ifndef _OPERAND_H_
#define _OPERAND_H_

#include <string>

class Operand{
	public:
		enum Types { REGISTER, LITERAL, LABEL, VARIABLE };
		enum DataTypes {FLOAT, INT};
		Operand(Types type, std::string value);
		Operand(Types type, int reg);
		std::string ToString();
		std::string ToAssemblyString();
		Types Type;
		DataTypes DataType;
		std::string Value;
		int Reg;
};

#endif
