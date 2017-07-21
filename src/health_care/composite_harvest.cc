#include "composite_harvest.h"
#include "harvest.h"
#include "health_state.h"
#include "null_harvest.h"

#include <vector>

namespace healthcare {
CompositeHarvest::CompositeHarvest()
    : harvest_strats_() {
  null_harvest_ = NullHarvest();
}

int CompositeHarvest::CalculateHarvest(const HealthState &state) const {
  return GetHarvestInRange(state.period).GetHarvest(state);
}

int CompositeHarvest::GetWorkingHarvest(const HealthState &state) const {
    return GetHarvestInRange(state.period).GetWorkingHarvest(state);
}

void CompositeHarvest::AddHarvest(std::shared_ptr<const Harvest> state) {
  harvest_strats_.push_back(state);
}

bool CompositeHarvest::InRange(int period) const {
  for (auto strat : harvest_strats_) {
    if (strat->InRange(period))
      return true;
  }
  return false;
}

const Harvest&
CompositeHarvest::GetHarvestInRange(int period) const {
  for (auto strat : harvest_strats_) {
    if (strat->InRange(period))
      return *strat;
  }
  return null_harvest_;
}
} // namespace healthcare
