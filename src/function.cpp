#include "function.hpp" 

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
