#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <string>

class Symbol{
	public:
		enum Types { INT, STRING, FLOAT };
		std::string name;
		Types type;
		union {
			int n;
			std::string s;
			float f;
		} value;
}

#endif
