#ifndef _IRI_H_
#define _IRI_H_

#include "operand.hpp"
#include <list>
#include <string>
#include <sstream>

class IRI{
	public:
		enum Types {
			STOREI, WRITEI, ADDI, MULTI, SUBI,
			DIVI, STOREF, WRITEF, ADDF, MULTF,
			SUBF, DIVF
		};

		IRI(Types type, Operand op1);
		IRI(Types type, Operand op1, Operand op2);
		IRI(Types type, Operand op1, Operand op2, Operand op3);

		static IRI* create(Types type, Operand op1) {
			return new IRI(type, op1);
		}
		static IRI* create(Types type, Operand op1, Operand op2) {
			return new IRI(type, op1, op2);
		}
		static IRI* create(Types type, Operand op1, Operand op2, Operand op3) {
			return new IRI(type, op1, op2, op3);
		}

		void PrintIRI(std::stringstream* stream);
		void PrintAssembly(std::stringstream* stream);

		list<Operand> Operands;
		Types Type;
};

#endif
