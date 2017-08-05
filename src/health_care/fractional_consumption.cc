#include "fractional_consumption.h"
#include <cmath>

namespace healthcare {

FractionalConsumption::FractionalConsumption(double j)
    : FractionalConsumption(j, 300) {}
FractionalConsumption::FractionalConsumption(double j, int max_investment)
    : j_(j), cache_(max_investment + 1) {
  for (int li = 0; li <= max_investment; ++li) {
    for (int h = 0; h <= 100; ++h) {
      cache_[li][h] = CalculateEnjoyment(h, li);
    }
  }
}

double FractionalConsumption::GetLifeEnjoyment(int health,
                                               int life_investment) const {
  return cache_[life_investment][health];
}

double FractionalConsumption::CalculateEnjoyment(int health,
                                                 int life_investment) const {
  return health * life_investment / (life_investment + j_);
}

} // namespace healthcare
