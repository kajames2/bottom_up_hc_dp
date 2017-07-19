#include "logistic_consumption.h"
#include <cmath>

namespace healthcare {

LogisticConsumption::LogisticConsumption(double k) : k_(k) {}

double LogisticConsumption::GetLifeEnjoyment(int life_investment,
                                             int health) const {
  return health * 1.0 /
         (1.0 + std::exp(-1 * k_ * life_investment));
}

} // namespace healthcare
