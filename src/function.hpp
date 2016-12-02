#include <string>
#include <list>
#include <sstream>
#include "iri.hpp"
#include "operand.hpp"

struct Function {
  Function(std::string asdf);
  ~Function();
  int num_params;
  std::string name;
  std::list<IRI*> iri_list;

  int get_next_temp();
  int get_next_local();
  int get_num_temps();
  int get_num_locals();

  int calc_temp_offset(int temp_num);
  int calc_param_offset(int param_num);
  int calc_local_offset(int local_num);
  int calc_return_offset();

  void register_allocate(Operand* ensure1, Operand* ensure2, Operand* allocate);

  void print_ir(std::stringstream& ss);
  void print_assembly(std::stringstream& ss);

  void finish();

  void generate_cfg();
  void calculate_liveness();
  
  private:
    int next_temp;
    int next_local;
};

// Types of symbols :
//  Functions (Pointer to function object)
//  Global variables (No other information)
//  Parameter (index in function)
//  Local variable (index in function)
//
//  Each symbol table stack frame has a number?
