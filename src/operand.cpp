#include "operand.hpp"

Operand::Operand(Types type, std::string value)
	:Type(type), Value(value) { }
Operand::Operand(Types type, int reg)
	:Type(type), Reg(reg) { }
