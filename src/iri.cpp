#include "iri.hpp"

IRI::IRI(Types type, Operand op1)
	:Type(type) {
		Operands.push_back(op1);
	}
IRI::IRI(Types type, Operand op1, Operand op2)
	:Type(type) {
		Operands.push_back(op1, op2);
	}
IRI::IRI(Types type, Operand op1, Operand op2, Operand op3)
	:Type(type) {
		Operands.push_back(op1, op2, op3);
	}

IRI::PrintIRI(std::stringstream* stream) {
}

IRI::PrintAssembly(std::stringstream* stream) {
}
