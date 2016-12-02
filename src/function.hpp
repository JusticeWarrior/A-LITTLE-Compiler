#include <string>
#include <list>
#include <sstream>
#include "iri.hpp"
#include "operand.hpp"
#include "register.hpp"
#include <unordered_set>
#include <sstream>

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

  void register_allocate(std::stringstream* stream, std::unordered_set<std::string> live_set, Operand* ensure1, Operand* ensure2, Operand* allocate);
  void print_ir(std::stringstream& ss);
  void print_assembly(std::stringstream& ss);

  void finish();

  void generate_cfg();
  void calculate_liveness();
  
  std::string variable_name_to_offset(std::string name);

  Register reg1;
  Register reg2;
  Register reg3;
  Register reg4;

  private:
    int next_temp;
    int next_local;

    void write_back_if_dirty(Register* reg, std::stringstream* stream);
    void overwrite_register(Register* reg, std::string op_name, std::stringstream* stream);
    void ensure_variable(std::stringstream* stream, std::unordered_set<std::string> live_set, Operand* ensure1, Operand* ensure2);
};

// Types of symbols :
//  Functions (Pointer to function object)
//  Global variables (No other information)
//  Parameter (index in function)
//  Local variable (index in function)
//
//  Each symbol table stack frame has a number?
