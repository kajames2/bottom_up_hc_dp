#include "shifted_logistic_regeneration.h"

#include <cmath>
#include <vector>

namespace healthcare {

ShiftedLogisticRegeneration::ShiftedLogisticRegeneration(double k) : k_(k) {}

int ShiftedLogisticRegeneration::GetHealthRegained(int health_investment,
                                                   int health) const {
  double h_frac = health/100.0;
  double i_frac = health_investment/100.0;
  return static_cast<int>(
      100*((std::exp(k_*i_frac)/(std::exp(k_*i_frac) + (1 - h_frac)/h_frac))-h_frac));
}

} // namespace healthcare
