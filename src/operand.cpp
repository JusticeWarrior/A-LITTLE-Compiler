#include "operand.hpp"
#include <iostream>

#define MAGIC -12321

Operand::Operand() {
	Type = NOTHING;
	Awful = MAGIC;
}
Operand::Operand(Types type, std::string value)
	:Type(type), Value(value), Awful(MAGIC) { }
Operand::Operand(Types type, int reg)
	:Type(type), Reg(reg), Awful(MAGIC) { }
std::string Operand::ToString() {
	if (Awful == MAGIC)
	  Awful = Reg;
	if (Type == NOTHING)
		return "";
	else if (Type == REGISTER)
		return "$T" + std::to_string(static_cast<long long>(Awful));
	else if (Type == LOCAL)
		return "$L" + std::to_string(static_cast<long long>(Awful));
	else if (Type == PARAMETER)
		return "$P" + std::to_string(static_cast<long long>(Awful));
	else if (Type == RETURN)
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
