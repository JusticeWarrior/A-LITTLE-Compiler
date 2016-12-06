#include "operand.hpp"
#include <iostream>

#define MAGIC -12321

Operand::Operand() {
	Type = NOTHING;
	Awful = MAGIC;
	AwfulType = MAGIC_TYPE;
}
Operand::Operand(Types type, std::string value)
	:Type(type), Value(value), Awful(MAGIC), AwfulType(MAGIC_TYPE) { }
Operand::Operand(Types type, int reg)
	:Type(type), Reg(reg), Awful(MAGIC), AwfulType(MAGIC_TYPE) { }

std::string Operand::ToString() {
	if (AwfulType == MAGIC_TYPE)
		AwfulType = Type;
	if (Awful == MAGIC)
	  Awful = Reg;

	if (AwfulType == NOTHING)
		return "";
	else if (AwfulType == REGISTER)
		return "$T" + std::to_string(static_cast<long long>(Awful));
	else if (AwfulType == LOCAL)
		return "$L" + std::to_string(static_cast<long long>(Awful));
	else if (AwfulType == PARAMETER)
		return "$P" + std::to_string(static_cast<long long>(Awful));
	else if (AwfulType == RETURN)
		return "$R";
	else
		return Value;
}
std::string Operand::ToAssemblyString() {
	if (Type == NOTHING)
		return "";
	else if (Type == REGISTER)
		return "r" + std::to_string(static_cast<long long>(Reg));
	else if (Type == LOCAL || Type == PARAMETER || Type == RETURN)
		return "$" + std::to_string(static_cast<long long>(Offset));
	else
		return Value;
}
