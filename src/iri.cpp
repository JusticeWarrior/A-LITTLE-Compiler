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
	if (Type == STOREI)
		*stream << ";STOREI " << Operands[0].ToString() << " " << Operands[1].ToString() << std::endl;
	if (Type == WRITEI)
		*stream << ";WRITEI " << Operands[0].ToString() << std::endl;
	if (Type == ADDI)
		*stream << ";ADDI " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
}

void IRI::PrintAssembly(std::stringstream* stream) {
}
