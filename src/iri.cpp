#include "iri.hpp"
#include "function.hpp"
#include <set>

IRI::IRI(Types type, Operand op1)
	:Type(type), dump(false) {
		Operands.push_back(op1);
	}
IRI::IRI(Types type, Operand op1, Operand op2)
	:Type(type), dump(false) {
		Operands.push_back(op1);
		Operands.push_back(op2);
	}
IRI::IRI(Types type, Operand op1, Operand op2, Operand op3)
	:Type(type), dump(false) {
		Operands.push_back(op1);
		Operands.push_back(op2);
		Operands.push_back(op3);
	}
std::string IRI::get_comparison(){
	std::string str = "";
	if (Operands[0].DataType == Operand::FLOAT)
	  str += "cmpr ";
	else
	  str += "cmpi ";
	str += Operands[0].ToAssemblyString() + " " + Operands[1].ToAssemblyString();
	return str;
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
	else if (Type == JSR)
		*stream << ";JSR " << Operands[0].ToString() << std::endl;
	else if (Type == PUSH)
		*stream << ";PUSH " << Operands[0].ToString() << std::endl;
	else if (Type == POP)
		*stream << ";POP " << Operands[0].ToString() << std::endl;
	else if (Type == RET)
		*stream << ";RET" << std::endl;
	else if (Type == LINK)
		*stream << ";LINK" << Operands[0].ToString() << std::endl;
	else if (Type == WRITES)
		*stream << ";WRITES " << Operands[0].ToString() << std::endl;
	else
		throw std::string("Unrecognized IRI");
	// Print the liveness set as well

	/*
	*stream << this << " PRED: ";
	for (auto it = predecessor_set.begin(); it != predecessor_set.end(); it++) {
	  *stream << (*it) << ", ";
	}
	*stream << "SUCC:";
	for (auto it = successor_set.begin(); it != successor_set.end(); it++) {
	  *stream << (*it) <<", ";
	}
	*stream << std::endl;
	*/
  
/*	
	*stream << ";{";
	for (auto it = in_set.begin(); it != in_set.end(); it++) {
	  *stream << *it << ", ";
	}
	*stream << "}" << std::endl;
	*/

/*
	*stream << ";{";
	for (auto it = live_set.begin(); it != live_set.end(); it++) {
	  *stream << *it << ", ";
	}
	*stream << "}" << std::endl << std::endl;
	*/
	
}

void IRI::PrintAssembly(std::stringstream* stream) {
	PrintIRI(stream);
	Operand::Operand dummy;
	if (Type == STOREI) {
		if (Operands[1].Type == Operand::REGISTER) {
			_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &Operands[1]);
		} else {
			_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &dummy);
		}
		*stream << "move " << Operands[0].ToAssemblyString() << " " << Operands[1].ToAssemblyString() << std::endl;
	}
	else if (Type == READI){
		_Function->register_allocate(stream, live_set, &dummy, &dummy, &Operands[0]);
		*stream << "sys readi " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == READF){
		_Function->register_allocate(stream, live_set, &dummy, &dummy, &Operands[0]);
		*stream << "sys readr " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == WRITEI){
		_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &dummy);
		*stream << "sys writei " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == ADDI) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "addi " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == MULTI) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "muli " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == SUBI) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "subi " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == DIVI) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "divi " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == STOREF){
		if (Operands[1].Type == Operand::REGISTER) {
			_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &Operands[1]);
		} else {
			_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &dummy);
		}
		*stream << "move " << Operands[0].ToAssemblyString() << " " << Operands[1].ToAssemblyString() << std::endl;
	}
	else if (Type == WRITEF){
		_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &dummy);
		*stream << "sys writer " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == ADDF) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "addr " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == MULTF) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "mulr " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == SUBF) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "subr " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == DIVF) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &Operands[2]);
		*stream << "move " << Operands[1].ToAssemblyString() << " " << Operands[2].ToAssemblyString()  << std::endl;
		*stream << "divr " << Operands[0].ToAssemblyString() << " " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == GT) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jgt " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == GE) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jge " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == LT) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jlt " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == LE) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jle " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == NE) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jne " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == EQ) {
		_Function->register_allocate(stream, live_set, &Operands[0], &Operands[1], &dummy);
		*stream << get_comparison() << std::endl;
		*stream << "jeq " << Operands[2].ToAssemblyString() << std::endl;
	}
	else if (Type == LABEL) {
		*stream << "label " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == JUMP) {
		*stream << "jmp " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == JSR) {
		*stream << "push r0" << std::endl;
		*stream << "push r1" << std::endl;
		*stream << "push r2" << std::endl;
		*stream << "push r3" << std::endl;
		*stream << "jsr " << Operands[0].ToAssemblyString() << std::endl;
		if (Operands[0].ToAssemblyString() != "main") {
			*stream << "pop r3" << std::endl;
			*stream << "pop r2" << std::endl;
			*stream << "pop r1" << std::endl;
			*stream << "pop r0" << std::endl;
		}
	}
	else if (Type == PUSH) {
		_Function->register_allocate(stream, live_set, &Operands[0], &dummy, &dummy);
		*stream << "push " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == POP) {
		if (Operands[0].Type == Operand::LABEL) {
			*stream << "pop" << std::endl;	
		} else {
			_Function->register_allocate(stream, live_set, &dummy, &dummy, &Operands[0]);
			*stream << "pop " << Operands[0].ToAssemblyString() << std::endl;
		}
	}
	else if (Type == RET) {
		*stream << "unlnk" << std::endl;
		*stream << "ret" << std::endl;
	}
	else if (Type == LINK) {
		*stream << "link " << Operands[0].ToAssemblyString() << std::endl;
	}
	else if (Type == WRITES)
		*stream << "sys writes " << Operands[0].ToAssemblyString() << std::endl;
	else
		throw std::string("Unrecognized assembly directive!");

	*stream << ";{";
	for (auto it = live_set.begin(); it != live_set.end(); it++) {
	  *stream << *it << ", ";
	}
	*stream << "}" << std::endl;
}


void IRI::populate_gen_kill() {
  switch(Type) {
    case ADDI: case MULTI: case SUBI: case DIVI: case ADDF: case SUBF: case MULTF: case DIVF:
      if (Operands[0].Type == Operand::REGISTER) gen_set.insert(Operands[0].ToString());
      if (Operands[1].Type == Operand::REGISTER) gen_set.insert(Operands[1].ToString());
      if (Operands[2].Type == Operand::REGISTER) kill_set.insert(Operands[2].ToString());
      break;

    case WRITEI: case WRITEF: case PUSH:
      if (Operands[0].Type == Operand::REGISTER) gen_set.insert(Operands[0].ToString());
      break;

    case READI: case READF: case POP:
      if (Operands[0].Type == Operand::REGISTER) kill_set.insert(Operands[0].ToString());
      break;

    case STOREI: case STOREF:
      if (Operands[0].Type == Operand::REGISTER) gen_set.insert(Operands[0].ToString());
      if (Operands[1].Type == Operand::REGISTER) kill_set.insert(Operands[1].ToString());
      break;

    case GT: case GE: case LT: case LE: case NE: case EQ:
      if (Operands[0].Type == Operand::REGISTER) gen_set.insert(Operands[0].ToString());
      if (Operands[1].Type == Operand::REGISTER) gen_set.insert(Operands[1].ToString());
      break;
  }
}

bool IRI::update_liveness_set() {
  // First update OUT set
  live_set.clear();
  for (auto it = successor_set.begin(); it != successor_set.end(); it++) {
    live_set.insert((*it)->in_set.begin(), (*it)->in_set.end());
  }

  // Now figure out the new in_set
  std::set<std::string> old_in_set;
  old_in_set.insert(in_set.begin(), in_set.end());

  // Set in set to the liveness set
  in_set.clear();
  in_set.insert(live_set.begin(), live_set.end());

  // Remove the kill
  for (auto it = kill_set.begin(); it != kill_set.end(); it++) {
    in_set.erase(*it);
  }
  // Add the gen
  for (auto it = gen_set.begin(); it != gen_set.end(); it++) {
    in_set.insert(*it);
  }
  std::set<std::string> new_in_set;
  new_in_set.insert(in_set.begin(), in_set.end());
  return new_in_set != old_in_set;
}

