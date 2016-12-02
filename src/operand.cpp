#include "operand.hpp"

Operand::Operand() {
	Type = NOTHING;
}
Operand::Operand(Types type, std::string value)
	:Type(type), Value(value) { }
Operand::Operand(Types type, int reg)
	:Type(type), Reg(reg) { }
std::string Operand::ToString() {
	if (Type == NOTHING)
		return "";
	else if (Type == REGISTER)
		return "$T" + std::to_string(static_cast<long long>(Reg));
	else if (Type == LOCAL)
		return "$L" + std::to_string(static_cast<long long>(Reg));
	else if (Type == PARAMETER)
		return "$P" + std::to_string(static_cast<long long>(Reg));
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
