#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>

class Register{
	public:
		Register();
		Register(std::string name);
		Register(int reg, std::string name);
		Register(int reg);
		std::string Name;
		int Dirty;
		int Reg;
};

#endif
