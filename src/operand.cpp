#include "operand.hpp"

Operand::Operand(Types type, std::string value)
	:Type(type), Value(value) { }
Operand::Operand(Types type, int reg)
	:Type(type), Reg(reg) { }
std::string Operand::ToString() {
	if (Type == REGISTER)
		return "$T" + std::to_string(static_cast<long long>(Reg));
	else if (Type == LOCAL)
		return "$L" + std::to_string(static_cast<long long>(Reg));
	else if (Type == PARAMETER)
		return "$P" + std::to_string(static_cast<long long>(Reg));
	else
		return Value;
}
std::string Operand::ToAssemblyString() {
	if (Type == REGISTER)
		return "r" + std::to_string(static_cast<long long>(Reg));
	else if (Type == LOCAL || Type == PARAMETER)
		if (Offset < 0)
		  return "$" + std::to_string(static_cast<long long>(Offset));
		else
		  return "$+" + std::to_string(static_cast<long long>(Offset));
	else
		return Value;
}
