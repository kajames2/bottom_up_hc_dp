#ifndef _INVESTMENT_H_
#define _INVESTMENT_H_

#include "health_state.h"

namespace healthcare {
struct Investment {
  Investment() {}
  Investment(int hi, int li) : health_investment(hi), life_investment(li) {}
  int health_investment;
  int life_investment;

  bool operator==(const Investment &other) const {
    return health_investment == other.health_investment &&
           life_investment == other.life_investment;
  }
};
} // namespace healthcare
#endif // _INVESTMENT_H_
