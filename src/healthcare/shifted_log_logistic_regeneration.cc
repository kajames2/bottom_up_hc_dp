#include "shifted_log_logistic_regeneration.h"

#include <cmath>
#include <vector>

namespace healthcare {

ShiftedLogLogisticRegeneration::ShiftedLogLogisticRegeneration(double alpha, double beta)
    : ShiftedLogLogisticRegeneration(alpha, beta, 300) {}
ShiftedLogLogisticRegeneration::ShiftedLogLogisticRegeneration(double alpha, double beta,
                                                 int max_investment)
    : alpha_(alpha), beta_(beta), CachedRegeneration(max_investment) {
  FillCache();
}

int ShiftedLogLogisticRegeneration::CalculateHealthRegained(
    int health, int health_investment) const {
  if (health == 0) {return 0;}
  double shift =
      alpha_ * std::pow((100 - health) / static_cast<double>(health), -1 / beta_);
  return static_cast<int>(100 / (1 + std::pow((health_investment + shift) / alpha_, -beta_)) -
                          health);
}

} // namespace healthcare
