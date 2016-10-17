#include "symbol.hpp"

// This class is a dataobject.  It is meant to represent the type and name of the storage location
// of a literal, the results of an expression, the results of a function call, or a symbol

struct DataObject {
  
  // Type definitions
  enum DataType {INT, FLOAT};
  enum RegisterType {TEMP, VAR};

  // Static
  static int temp_num;

  // Members
  std::string name;
  DataType data_type;

  // Relevant only for VAR
  std::string name;

  // Relevant only for TEMP
  int number;

  // Initialize var type
  DataObject(Symbol sym);

  // Initialize temp type
  DataObject(DataType type);

};

// Arithmetic operations
struct Operation {
  enum Type {
    ADD, SUB, MUL, DIV
  }
  Type type;
};
