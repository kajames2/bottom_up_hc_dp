#include "retirement_harvest.h"
#include "health_state.h"

#include <cmath>

namespace healthcare {
RetirementHarvest::RetirementHarvest(int first_period, double earning_frac)
    : first_period_(first_period), earning_frac_(earning_frac) {}

int RetirementHarvest::CalculateHarvest(const HealthState &state) const {
  return std::round(state.total_working_harvest * earning_frac_ /
                    (first_period_ - 1));
}

bool RetirementHarvest::InRange(int period) const {
  return period >= first_period_;
}
} // namespace healthcare
