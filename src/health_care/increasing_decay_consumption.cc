#include "increasing_decay_consumption.h"
#include <cmath>

namespace healthcare {

IncreasingDecayConsumption::IncreasingDecayConsumption(double alpha, double c, double beta)
    : alpha_(alpha), c_(c), beta_(beta) {}

double IncreasingDecayConsumption::GetLifeEnjoyment(int health, int life_investment) const {
  return c_ * (beta_ * health / 100.0 + (1 - beta_)) *
         (1 - std::exp(-alpha_ * life_investment));
}

} // namespace healthcare
