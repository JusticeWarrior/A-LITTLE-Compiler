#include "register.hpp"

Register::Register() {
	Name = "";
	Dirty = 0;
	Reg = 0;
}
Register::Register(std::string name)
	:Name(name), Dirty(0), Reg(0) { }

Register::Register(int reg, std::string name)
	:Name(name), Reg(reg), Dirty(0) {}

Register::Register(int reg)
	:Reg(reg), Name(""), Dirty(0) {}
