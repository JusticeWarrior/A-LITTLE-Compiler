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

int DataObject::temp_num = 0;
