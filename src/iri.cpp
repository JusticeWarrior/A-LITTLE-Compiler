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
	else if (Type == WRITEI)
		*stream << ";WRITEI " << Operands[0].ToString() << std::endl;
	else if (Type == READI)
		*stream << ";READI " << Operands[0].ToString() << std::endl;
	else if (Type == ADDI)
		*stream << ";ADDI " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == MULTI)
		*stream << ";MULTI " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == SUBI)
		*stream << ";SUBI " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == DIVI)
		*stream << ";DIVI " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == STOREF)
		*stream << ";STOREF " << Operands[0].ToString() << " " << Operands[1].ToString() << std::endl;
	else if (Type == WRITEF)
		*stream << ";WRITEF " << Operands[0].ToString() << std::endl;
	else if (Type == READF)
		*stream << ";READF " << Operands[0].ToString() << std::endl;
	else if (Type == ADDF)
		*stream << ";ADDF " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == MULTF)
		*stream << ";MULTF " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == SUBF)
		*stream << ";SUBF " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == DIVF)
		*stream << ";DIVF " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == GT)
		*stream << ";GT " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == GE)
		*stream << ";GE " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == LT)
		*stream << ";LT " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == LE)
		*stream << ";LE " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == NE)
		*stream << ";NE " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == EQ)
		*stream << ";EQ " << Operands[0].ToString() << " " << Operands[1].ToString() << " " << Operands[2].ToString() << std::endl;
	else if (Type == JUMP)
		*stream << ";JUMP " << Operands[0].ToString() << std::endl;
	else if (Type == LABEL)
		*stream << ";LABEL " << Operands[0].ToString() << std::endl;
	else
		throw std::string("Unrecognized IRI");
}

void IRI::PrintAssembly(std::stringstream* stream) {
	if (Type == STOREI)
		*stream << "move " << Operands[0].ToAssemblyString() << " " << Operands[1].ToAssemblyString() << std::endl;
	else if (Type == WRITEI)
		*stream << "sys writei " << Operands[0].ToAssemblyString() << std::endl;
	else if (Type == ADDI) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "addi " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == MULTI) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "muli " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == SUBI) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "subi " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == DIVI) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "divi " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == STOREF)
		*stream << "move " << Operands[0].ToAssemblyString() << " " << Operands[1].ToAssemblyString() << std::endl;
	else if (Type == WRITEF)
		*stream << "sys writer " << Operands[0].ToAssemblyString() << std::endl;
	else if (Type == ADDF) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "addr " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == MULTF) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "mulr " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == SUBF) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "subr " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == DIVF) {
		*stream << "move " << Operands[0].ToAssemblyString() << " r0"  << std::endl;
		*stream << "divr " << Operands[1].ToAssemblyString() << " r0" << std::endl;
		*stream << "move r0 " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == LABEL) {
		*stream << "label " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == JUMP) {
		*stream << "jmp " << Operands[0].ToAssemblyString() << std::endl;
	}
	else
		throw std::string("Unrecognized assembly directive!");
}
