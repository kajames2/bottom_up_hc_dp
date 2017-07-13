#include "logistic_regeneration.h"
#include <cmath>
#include <vector>

namespace healthcare {

LogisticRegeneration::LogisticRegeneration(double gamma, double sigma, double r)
    : gamma_(gamma), sigma_(sigma), r_(r) {}

int LogisticRegeneration::GetHealthRegained(int health_investment,
                                            int health) const {
  return static_cast<int>(
      gamma_ * (1 - std::exp(-1 * sigma_ * health_investment)) /
      (1.0 + std::exp((-1) * sigma_ * health_investment - r_)));
}

} // namespace healthcare
