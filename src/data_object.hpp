#ifndef _DATA_OBJECT_H_
#define _DATA_OBJECT_H_

#include "symbol.hpp"
#include "operand.hpp"
#include "iri.hpp"

#define half_expr_t std::pair<int ,DataObject*>
#define half_expr_is_valid(half) \
  ((half).second !=0 )

class LittleParser;

// This class is a dataobject.  It is meant to represent the type and name of the storage location
// of a literal, the results of an expression, the results of a function call, or a symbol

struct DataObject {
  
  // Type definitions
  enum DataType {INT, FLOAT, STRING};
  enum RegisterType {TEMP, VAR};

  // Static
  //static int temp_num;
  // The most awful thing you've seen all day
  static LittleParser* parser;

  // Members
  DataType data_type;
  RegisterType reg_type;

  // Relevant only for VAR
  std::string name;
  Symbol* symbol; // A pointer to the symbol table entry

  // Relevant only for TEMP
  int number;

  // Initialize var type
  DataObject(Symbol* sym);

  // Initialize temp type
  DataObject(DataType type);

  Operand get_operand();

  // Null pointer indicates error
  static IRI* get_IRI(DataObject* lhs, int op, DataObject* rhs, DataObject* result);

  // Takes a half expression (op, lhs) and a data object (rhs) and:
  // - generates a result DataObject
  // - cleans up the inputs
  // - sets IRI* iri to NULL or and iri if one needs to be generated
  static DataObject* evaluate_expression(half_expr_t* half_expr, IRI** iri, DataObject* rhs);

};

// Arithmetic operations
enum ArithmeticOperation{
  ADD, SUB, MUL, DIV
};

#endif
