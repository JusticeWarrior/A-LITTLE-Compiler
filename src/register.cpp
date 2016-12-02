#include "register.hpp"

Register::Register() {
	Name = "";
	Dirty = 0;
	Reg = 0;
}
Register::Register(std::string name)
	:Name(name) { }

Register::Register(int reg, std::string name)
	:Name(name), Reg(reg) {}

Register::Register(int reg)
	:Reg(reg), Name("") {}
