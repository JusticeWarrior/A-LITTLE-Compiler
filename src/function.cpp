#include "function.hpp" 
#include <sstream>
#include <iostream>
#include <map>
#include <set>

Function::Function(std::string name) :
  next_temp(1),
  next_local(1),
  name(name),
  num_params(0),
  reg1(0),
  reg2(2),
  reg3(2),
  reg4(3)
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
      static_cast<long long>(get_num_locals()+get_num_temps())
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
  
  // Make sure everyone knows which function they're in
  for (auto it = iri_list.begin(); it != iri_list.end(); it ++) {
    (*it)->_Function = this;
  }
  // Do liveness analysis
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
    if (changed) {
      work_list.insert(iri->predecessor_set.begin(), iri->predecessor_set.end());
    }
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

void Function::write_back_if_dirty(Register* reg, std::stringstream* stream) {
  if (reg->Dirty) {
    *stream << "move r" << std::to_string(static_cast<long long>(reg->Reg)) << " $" << variable_name_to_offset(reg->Name) << std::endl;
	reg->Dirty = 0;
  }
}

void Function::overwrite_register(Register* reg, std::string op_name, std::stringstream* stream) {
    *stream << "move $" << variable_name_to_offset(op_name) << " r" << std::to_string(static_cast<long long>(reg->Reg)) << std::endl;
}

void Function::ensure_variable(std::stringstream* stream, std::unordered_set<std::string> live_set, Operand* ensure1, Operand* ensure2) {
  if (ensure1->Type != Operand::NOTHING) {
  	// Check if already in register
  	if (reg1.Name == ensure1->ToString()) {
	  ensure1->Reg = 0;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg2.Name == ensure1->ToString()) {
	  ensure1->Reg = 1;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg3.Name == ensure1->ToString()) {
	  ensure1->Reg = 2;
	  ensure1->Type = Operand::REGISTER;
	}
  	else if (reg4.Name == ensure1->ToString()) {
	  ensure1->Reg = 3;
	  ensure1->Type = Operand::REGISTER;
	}
	// Find the first unused register
	else {
	  if (live_set.find(reg1.Name) == live_set.end() && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg1.Name)) {
	    overwrite_register(&reg1, ensure1->ToString(), stream);
	    reg1.Name = ensure1->ToString();
	    ensure1->Reg = 0;
	    ensure1->Type = Operand::REGISTER;
	    reg1.Dirty = 0;
	  }
	  else if (live_set.find(reg2.Name) == live_set.end() && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg2.Name)) {
	    overwrite_register(&reg2, ensure1->ToString(), stream);
	    reg2.Name = ensure1->ToString();
	    ensure1->Reg = 1;
	    ensure1->Type = Operand::REGISTER;
	    reg2.Dirty = 0;
	  }
	  else if (live_set.find(reg3.Name) == live_set.end() && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg3.Name)) {
	    overwrite_register(&reg3, ensure1->ToString(), stream);
	    reg3.Name = ensure1->ToString();
	    ensure1->Reg = 2;
	    ensure1->Type = Operand::REGISTER;
	    reg3.Dirty = 0;
	  }
	  else if (live_set.find(reg4.Name) == live_set.end() && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg4.Name)) {
	    overwrite_register(&reg4, ensure1->ToString(), stream);
	    reg4.Name = ensure1->ToString();
	    ensure1->Reg = 3;
	    ensure1->Type = Operand::REGISTER;
	    reg4.Dirty = 0;
	  }
	  // We have to spill...
	  else {
	    // Find the first register not used by ensure2
		if (ensure2->Type == Operand::NOTHING || ensure2->ToString() != reg1.Name) {
		  // Spill r1
	      write_back_if_dirty(&reg1, stream);
	      overwrite_register(&reg1, ensure1->ToString(), stream);
	      reg1.Name = ensure1->ToString();
	      ensure1->Reg = 0;
	      ensure1->Type = Operand::REGISTER;
		} else {
		  // Spill r2
	      write_back_if_dirty(&reg2, stream);
	      overwrite_register(&reg2, ensure1->ToString(), stream);
	      reg2.Name = ensure1->ToString();
	      ensure1->Reg = 1;
	      ensure1->Type = Operand::REGISTER;
		}
	  }
	}
  }
}

void Function::register_allocate(std::stringstream* stream, std::unordered_set<std::string> live_set, Operand* ensure1, Operand* ensure2, Operand* allocate) {
  // Ensure variables
  ensure_variable(stream, live_set, ensure1, ensure2);
  ensure_variable(stream, live_set, ensure2, ensure1);
  
  // Allocate the third variable
  if (ensure1->Type != Operand::NOTHING && allocate->ToString() == ensure1->ToString()) {
  	if (reg1.Name == ensure1->ToString()) {
	  reg1.Dirty = 1;
	}
  	else if (reg2.Name == ensure1->ToString()) {
	  reg2.Dirty = 1;
	}
  	else if (reg3.Name == ensure1->ToString()) {
	  reg3.Dirty = 1;
	}
  	else {
	  reg4.Dirty = 1;
	}
  }
  else if (ensure2->Type != Operand::NOTHING && allocate->ToString() == ensure2->ToString()) {
  	if (reg1.Name == ensure2->ToString()) {
	  reg1.Dirty = 1;
	}
  	else if (reg2.Name == ensure2->ToString()) {
	  reg2.Dirty = 1;
	}
  	else if (reg3.Name == ensure2->ToString()) {
	  reg3.Dirty = 1;
	}
  	else {
	  reg4.Dirty = 1;
	}
  }
  else if (allocate->Type != Operand::NOTHING) {
	// Find the first unused register
	  if (live_set.find(reg1.Name) == live_set.end() && (ensure1->Type != Operand::NOTHING || ensure1->ToString() != reg1.Name) && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg1.Name)) {
	    reg1.Name = allocate->ToString();
	    allocate->Reg = 0;
	    allocate->Type = Operand::REGISTER;
	    reg1.Dirty = 1;
	  }
	  else if (live_set.find(reg2.Name) == live_set.end() && (ensure1->Type != Operand::NOTHING || ensure1->ToString() != reg2.Name) && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg2.Name)) {
	    reg2.Name = allocate->ToString();
	    allocate->Reg = 1;
	    allocate->Type = Operand::REGISTER;
	    reg2.Dirty = 1;
	  }
	  else if (live_set.find(reg3.Name) == live_set.end() && (ensure1->Type != Operand::NOTHING || ensure1->ToString() != reg3.Name) && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg3.Name)) {
	    reg3.Name = allocate->ToString();
	    allocate->Reg = 2;
	    allocate->Type = Operand::REGISTER;
	    reg3.Dirty = 1;
	  }
	  else if (live_set.find(reg4.Name) == live_set.end() && (ensure1->Type != Operand::NOTHING || ensure1->ToString() != reg4.Name) && (ensure2->Type != Operand::NOTHING || ensure2->ToString() != reg4.Name)) {
	    reg4.Name = allocate->ToString();
	    allocate->Reg = 3;
	    allocate->Type = Operand::REGISTER;
	    reg4.Dirty = 1;
	  }
	  // We have to spill...
	  else {
	    // Find the first register not used by ensure2
		if ((ensure1->Type == Operand::NOTHING || ensure1->ToString() != reg1.Name) && (ensure2->Type == Operand::NOTHING || ensure2->ToString() != reg1.Name)) {
		  // Spill r1
	      write_back_if_dirty(&reg1, stream);
	      reg1.Name = allocate->ToString();
	      allocate->Reg = 0;
	      allocate->Type = Operand::REGISTER;
	      reg1.Dirty = 1;
		} else if ((ensure1->Type == Operand::NOTHING || ensure1->ToString() != reg2.Name) && (ensure2->Type == Operand::NOTHING || ensure2->ToString() != reg2.Name)) {
		  // Spill r2
	      write_back_if_dirty(&reg2, stream);
	      reg2.Name = allocate->ToString();
	      allocate->Reg = 1;
	      allocate->Type = Operand::REGISTER;
	      reg2.Dirty = 1;
		} else {
		  // Spill r3
	      write_back_if_dirty(&reg3, stream);
	      reg3.Name = allocate->ToString();
	      allocate->Reg = 2;
	      allocate->Type = Operand::REGISTER;
	      reg3.Dirty = 1;
		}
	  }
    
  }
}
