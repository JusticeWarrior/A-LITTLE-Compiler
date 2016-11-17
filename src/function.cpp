#include "function.hpp" 
#include <sstream>
#include <iostream>

Function::Function(std::string name) :
  next_temp(1), next_local(1), name(name), num_params(0)
{}

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

void Function::finish(){
  std::stringstream ss;
  // Add link statement
  iri_list.push_front(IRI::create(
    IRI::LINK, Operand(Operand::LITERAL, std::to_string(
      static_cast<long long>(num_params)
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
    }
    (*it)->PrintAssembly(&ss); // [???]
  }
  std::cerr << ss.rdbuf(); // [???]

}
