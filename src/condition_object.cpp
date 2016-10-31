#include "condition_object.hpp"

ConditionObject::ConditionObject(
  DataObject* lhs,
  DataObject* rhs,
  comp_t comp
):
  lhs(lhs), rhs(rhs), comparison(comp)
{}

void ConditionObject::invert() {
  comparison = static_cast<comp_t>(7-comparison);
}

IRI* ConditionObject::generate_jump(int label){
  std::string label_string = 
  std::string("L") +
  std::to_string(static_cast<unsigned long long>(label));
  if (comparison == TRUE) {
    return IRI::create(
      IRI::JUMP,
      Operand(Operand::LABEL, label_string)
    );
  }
  else if (comparison == FALSE) {
    return 0;
  }
  else {
    IRI::Types type;
    switch(comparison) {
      case GT: type = IRI::GT; break; 
      case LT: type = IRI::LT; break; 
      case EQ: type = IRI::EQ; break;  
      case NE: type = IRI::NE; break;
      case GE: type = IRI::GE; break;
      case LE: type = IRI::LE; break; 
    };
    return IRI::create(
      type,
      lhs->get_operand(),
      rhs->get_operand(),
      Operand(Operand::LABEL, label_string)
    );
  }
}
