#include "data_object.hpp"

DataObject::DataObject(Symbol sym) :
  name(sym.Name),
  reg_type(RegisterType::VAR)

{
  if (sym.Type == Symbol::INT)
    data_type = INT;
  else if (sym.Type == Symbol::FLOAT)
    data_type = FLOAT;
  else
    data_type = STRING;
}

DataObject::DataObject(DataType type) :
  data_type(type),
  reg_type(TEMP),
  number(temp_num++)
{}

Operand DataObject::get_operand() {
  if (reg_type == TEMP)
    return Operand(Operand::REGISTER, number);
  else
    return Operand(Operand::REGISTER, name);
}

IRI* DataObject::get_IRI(DataObject* lhs, int op, DataObject* rhs, DataObject* result){
  bool is_float;
  IRI::Types type;
  if ( lhs == 0 || rhs == 0) {
    return 0;
  }

  if (lhs->data_type == DataObject::FLOAT)
    is_float = true;
  else
    is_float = false;

  switch(op) {
    case ADD: type = is_float ? IRI::ADDF : IRI::ADDI; break;
    case SUB: type = is_float ? IRI::SUBF : IRI::SUBI; break;
    case MUL: type = is_float ? IRI::MULTF : IRI::MULTI; break;
    case DIV: type = is_float ? IRI::DIVF : IRI::DIVI; break;
  };

  return IRI::create(type, lhs->get_operand(), rhs->get_operand(), result->get_operand());
}
DataObject* DataObject::evaluate_expression(half_expr_t* half_expr, IRI** iri, DataObject* rhs) {
    DataObject* lhs = half_expr->second;
    DataObject* result;
    int op = half_expr->first;
    if (half_expr_is_valid(*half_expr)) {
      result = new DataObject(lhs->data_type);
      *iri = DataObject::get_IRI(lhs, op, rhs, result);
      return result;
    }
    else {
      *iri = 0;
      return rhs;
    }
  } 

int DataObject::temp_num = 0;
