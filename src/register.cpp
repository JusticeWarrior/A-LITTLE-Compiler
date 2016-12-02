#include "register.hpp"

Register::Register() {
	Name = "";
	Dirty = 0;
}
Register::Register(std::string name)
	:Name(name) { }
