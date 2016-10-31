#ifndef _KLJHDFLKJHSLKJHEJSDEFJ_H_
#define _KLJHDFLKJHSLKJHEJSDEFJ_H_

#include "iri.hpp"
#include "data_object.hpp"

class ConditionObject {
  public:
    enum comp_t {
      GT=0,
      LT=1,
      EQ=2,
      TRUE=3,
      FALSE=4,
      NE=5,
      GE=6,
      LE=7
    };
  private:
    DataObject* lhs;
    DataObject* rhs;
    comp_t comparison;

  public:
    ConditionObject(DataObject* lhs, DataObject* rhs, comp_t comp);
    void invert();
    IRI* generate_jump(int label);
};

#endif
