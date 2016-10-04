#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>

class Symbol{
	public:
		union T {
			int n;
			std::string s;
			float f;
		};
		enum Types { INT, STRING, FLOAT };
		Symbol(std::string name, Types type, T value);
		std::string Name;
		Types Type;
		T Value;
}

#endif
