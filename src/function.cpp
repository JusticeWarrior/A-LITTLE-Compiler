#include "function.hpp" 
#include <sstream>
#include <iostream>

Function::Function(std::string name) :
  next_temp(1), next_local(1), name(name), num_params(0)
{}

Function::~Function() {
  for (auto it = iri_list.begin(); it != iri_list.end(); it++) {
    delete *it;
  }
}

int Function::get_next_temp() {
  return next_temp++;
}

int Function::get_next_local() {
  return next_local++;
}

int Function::get_num_temps() {
  return next_temp - 1;
}

int Function::get_num_locals() {
  return next_local - 1;
}

int Function::calc_temp_offset(int temp_num) {
  return -(get_num_locals() + temp_num);
}

int Function::calc_param_offset(int param_num) {
  return 6 + num_params - param_num;
}

int Function::calc_local_offset(int local_num) {
  return -local_num;
}

int Function::calc_return_offset() {
  return 6 + num_params;
}

void Function::finish(){
 // std::stringstream ss;
  // Add link statement
  iri_list.push_front(IRI::create(
    IRI::LINK, Operand(Operand::LITERAL, std::to_string(
      static_cast<long long>(get_num_locals())
    ))
  ));
  // Add label
  iri_list.push_front(IRI::create(IRI::LABEL, Operand(Operand::LABEL, name)));
  // Iterate through all iri nodes
  for (auto it=iri_list.begin(); it!= iri_list.end(); it++) {
    for (auto op=(*it)->Operands.begin(); op != (*it)->Operands.end(); op++){
      if (op->Type == Operand::LOCAL) {
	op->Offset = calc_local_offset(op->Reg);
      }
      if (op->Type == Operand::PARAMETER){
	op->Offset = calc_param_offset(op->Reg);
      }
      if (op->Type == Operand::REGISTER) {
	op->Offset = calc_temp_offset(op->Reg);
      }
      if (op->Type == Operand::RETURN) {
	op->Offset = calc_return_offset();
      }
    }
   // (*it)->PrintAssembly(&ss); // [???]
  }
  //std::cerr << ss.rdbuf(); // [???]

}

void Function::print_ir(std::stringstream& ss) {
  for (auto i = iri_list.begin(); i != iri_list.end(); i++)
    (**i).PrintIRI(&ss);
}

void Function::print_assembly(std::stringstream& ss) {
  for (auto i = iri_list.begin(); i != iri_list.end(); i++)
    (**i).PrintAssembly(&ss);
}

void Function::register_allocate(Operand* ensure1, Operand* ensure2, Operand* allocate) {
  if (ensure1->Type != Operand::NOTHING) {
  	if (reg1.Name == ensure1.ToString()) {
	  ensure1->Reg = 0;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg2.Name == ensure1.ToString()) {
	  ensure1->Reg = 1;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg3.Name == ensure1.ToString()) {
	  ensure1->Reg = 2;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg4.Name == ensure1.ToString()) {
	  ensure1->Reg = 3;
	  ensure1->Type = Operand::REGISTER;
	}
	else {
	  
	}
  }
  
  if (ensure2->Type != Operand::NOTHING) {
  	
  }
  
  if (allocate->Type != Operand::NOTHING) {
  	
  }
}
