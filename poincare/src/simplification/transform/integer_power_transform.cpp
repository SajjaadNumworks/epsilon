#include "transform.h"
#include <assert.h>
#include <poincare/integer.h>
#include <poincare/power.h>
#include <poincare/multiplication.h>
#include <poincare/division.h>
#include <utility>

namespace Poincare {

bool Simplification::IntegerPowerTransform(Expression * captures[]) {
  Power * p = static_cast<Power *>(captures[0]);
  Integer * i1 = static_cast<Integer *>(captures[1]);
  Integer * i2 = static_cast<Integer *>(captures[2]);

  if (i2->isNegative()) {
    if (i2->isEqualTo(Integer(-1))) {
      return false;
    }
    Integer absI2 = *i2;
    absI2.setNegative(false);
    Expression * operands[2] = {new Integer(Integer::Power(*i1, absI2)), new Integer(-1)};
    Power * d = new Power(operands, false);
    static_cast<Hierarchy *>(p->parent())->replaceOperand(p, d, true);
    return true;
  }
  Integer * r = new Integer(Integer::Power(*i1, *i2));
  static_cast<Hierarchy *>(p->parent())->replaceOperand(p, r, true);
  return true;
}

}
