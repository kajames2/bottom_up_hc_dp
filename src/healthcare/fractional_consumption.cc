#include "fractional_consumption.h"
#include <cmath>

#include <iostream>
#include <memory>

namespace healthcare {

FractionalConsumption::FractionalConsumption(double j)
    : FractionalConsumption(j, 300) {}
FractionalConsumption::FractionalConsumption(double j, int max_investment)
    : j_(j), CachedConsumption(max_investment) {
  FillCache();
}

double
FractionalConsumption::CalculateLifeEnjoyment(int health,
                                              int life_investment) const {
  return health * life_investment / (life_investment + j_);
}

} // namespace healthcare
