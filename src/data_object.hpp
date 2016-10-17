#include "symbol.hpp"
#include "operand.hpp"
#include "iri.hpp"

// This class is a dataobject.  It is meant to represent the type and name of the storage location
// of a literal, the results of an expression, the results of a function call, or a symbol

struct DataObject {
  
  // Type definitions
  enum DataType {INT, FLOAT, STRING};
  enum RegisterType {TEMP, VAR};

  // Static
  static int temp_num;

  // Members
  DataType data_type;
  RegisterType reg_type;

  // Relevant only for VAR
  std::string name;

  // Relevant only for TEMP
  int number;

  // Initialize var type
  DataObject(Symbol sym);

  // Initialize temp type
  DataObject(DataType type);

  Operand get_operand();

  // Null pointer indicates error
  static IRI* get_IRI(DataObject* lhs, int op, DataObject* rhs);


};

// Arithmetic operations
enum ArithmeticOperation{
  ADD, SUB, MUL, DIV
};

