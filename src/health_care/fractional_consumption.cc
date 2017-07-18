#include "fractional_consumption.h"
#include <cmath>

namespace healthcare {

FractionalConsumption::FractionalConsumption(double j) : j_(j) {}

double FractionalConsumption::GetLifeEnjoyment(int life_investment,
                                               int health) const {
  return health * life_investment/(life_investment + j_);
}

} // namespace healthcare
