#include "function.hpp" 

Function::Function(std::string name, int num_params) :
  next_temp(1), next_local(1), name(name), num_params(num_params)
{}

int Function::get_next_temp() {
  return next_temp++;
}

int Function::get_next_local() {
  return next_local++;
}
