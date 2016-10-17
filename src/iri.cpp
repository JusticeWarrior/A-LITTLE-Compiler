#include "iri.hpp"

IRI::IRI(Types type, Operand op1)
	:Type(type) {
		Operands.push_back(op1);
	}
IRI::IRI(Types type, Operand op1, Operand op2)
	:Type(type) {
		Operands.push_back(op1);
		Operands.push_back(op2);
	}
IRI::IRI(Types type, Operand op1, Operand op2, Operand op3)
	:Type(type) {
		Operands.push_back(op1);
		Operands.push_back(op2);
		Operands.push_back(op3);
	}

void IRI::PrintIRI(std::stringstream* stream) {
	//*stream << "Symbol table " << name << std::endl;
	
	//if (Type == Types.STOREI)
		//*stream << ";STOREI " << name << std::endl;
}

void IRI::PrintAssembly(std::stringstream* stream) {
}
