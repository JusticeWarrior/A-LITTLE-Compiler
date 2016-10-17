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

int DataObject::temp_num = 0;
