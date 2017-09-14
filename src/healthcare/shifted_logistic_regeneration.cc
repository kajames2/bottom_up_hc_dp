#include "shifted_logistic_regeneration.h"

#include <cmath>
#include <vector>

namespace healthcare {

ShiftedLogisticRegeneration::ShiftedLogisticRegeneration(double k)
    : ShiftedLogisticRegeneration(k, 300) {}
ShiftedLogisticRegeneration::ShiftedLogisticRegeneration(double k,
                                                         int max_investment)
    : k_(k), CachedRegeneration(max_investment) {
  FillCache();
}

int ShiftedLogisticRegeneration::CalculateHealthRegained(
    int health, int health_investment) const {
  return static_cast<int>(100 * std::exp(k_ * health_investment) /
                              (std::exp(k_ * health_investment) +
                               (100 - health) / static_cast<double>(health)) -
                          health);
}

} // namespace healthcare
