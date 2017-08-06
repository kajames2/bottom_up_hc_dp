#include "linear_harvest.h"
#include "health_state.h"

#include <cmath>

namespace healthcare {
LinearHarvest::LinearHarvest(int first_period, int last_period, double harvest_rate)
    : harvest_rate_(harvest_rate)
    , first_period_(first_period)
    , last_period_(last_period) {}

int LinearHarvest::CalculateHarvest(const HealthState& state) const {
  return std::round(state.health * harvest_rate_);
}

bool LinearHarvest::InRange(int period) const {
  return first_period_ <= period && period <= last_period_;
}
}
