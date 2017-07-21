#include "shifted_logistic_regeneration.h"

#include <cmath>
#include <vector>

namespace healthcare {

ShiftedLogisticRegeneration::ShiftedLogisticRegeneration(double k) : k_(k) {}

int ShiftedLogisticRegeneration::GetHealthRegained(int health_investment,
                                                   int health) const {
  return static_cast<int>(
      100*std::exp(k_*health_investment)/(std::exp(k_*health_investment) + (100 - health)/static_cast<double>(health))-health);
}

} // namespace healthcare
