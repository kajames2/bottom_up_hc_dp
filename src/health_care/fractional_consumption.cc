#include "fractional_consumption.h"
#include <cmath>

namespace healthcare {

FractionalConsumption::FractionalConsumption(double j) : j_(j), cache_(301) {
  for (int li = 0; li <= 300; ++li) {
    for (int h = 0; h <= 100; ++h) {
      cache_[li][h] = CalculateEnjoyment(li, h);
    }
  }
}

double FractionalConsumption::GetLifeEnjoyment(int life_investment,
                                               int health) const {
  return cache_[life_investment][health];
} 

double FractionalConsumption::CalculateEnjoyment(int life_investment,
                                               int health) const {
  return health * life_investment/(life_investment + j_);
}

} // namespace healthcare
