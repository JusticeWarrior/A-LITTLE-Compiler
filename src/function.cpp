#include "function.hpp" 
#include <sstream>
#include <iostream>
#include <map>
#include <set>

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
  //
  generate_cfg();
  calculate_liveness();

}

void Function::print_ir(std::stringstream& ss) {
  for (auto i = iri_list.begin(); i != iri_list.end(); i++)
    (**i).PrintIRI(&ss);
}

void Function::print_assembly(std::stringstream& ss) {
  for (auto i = iri_list.begin(); i != iri_list.end(); i++)
    (**i).PrintAssembly(&ss);
}


void Function::generate_cfg() {
  // Step 1, build  a map of all of the labels
  std::map<std::string, IRI*> label_dict;
  for (auto it = iri_list.begin(); it != iri_list.end(); it++) {
    if ((*it)->Type == IRI::LABEL)
      label_dict[(*it)->Operands[0].ToString()] = *it;
  }

  // Step 2, connect all of the predecessors and successors
  for (auto it = iri_list.begin(); it != iri_list.end(); it++) {
    IRI* iri = *it;
    if (std::next(it) != iri_list.end() && (*it)->Type != IRI::JUMP) {
      iri->successor_set.insert( *std::next(it) );
      (*std::next(it))->predecessor_set.insert( iri);
    }
    if ( iri->Type == IRI::JUMP ) {
      iri->successor_set.insert( label_dict[iri->Operands[0].ToString()] );
      label_dict[iri->Operands[0].ToString()]->predecessor_set.insert(iri);
    }
    if (
      iri->Type == IRI::GT ||
      iri->Type == IRI::GE ||
      iri->Type == IRI::LT ||
      iri->Type == IRI::LE ||
      iri->Type == IRI::EQ ||
      iri->Type == IRI::NE
    ) {
      iri->successor_set.insert(label_dict[iri->Operands[2].ToString()]);
      label_dict[iri->Operands[2].ToString()]->predecessor_set.insert(iri);
    }
      
  }
}

void Function::calculate_liveness() {
  // Calulate all of the gen sets amd kill sets
  for (auto it = iri_list.begin(); it != iri_list.end(); it++) {
    (*it)->populate_gen_kill();
  }

  // Go through the worklist algorithm
  IRI* iri;
  bool changed;
  std::set<IRI*> work_list;
  work_list.insert(iri_list.begin(), iri_list.end());
  while(work_list.size() != 0) {
    iri = *work_list.begin();
    work_list.erase(work_list.begin());

    changed = iri->update_liveness_set();
    if (changed) work_list.insert(iri->predecessor_set.begin(), iri->predecessor_set.end());
  }
} //


std::string Function::variable_name_to_offset(std::string name) {
  long long offset;
  long long reg_num;
  if (name[0] != '$')
    return name;
  reg_num = std::stoi(name.erase(0,2));
  if (name[1] == 'L')
    offset = calc_local_offset(reg_num);
  if (name[1] == 'P')
    offset = calc_param_offset(reg_num);
  if (name[1] == 'T')
    offset = calc_temp_offset(reg_num);
  if (name[1] == 'R')
    offset = calc_return_offset();
  return std::string("$") + std::to_string(offset);
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
