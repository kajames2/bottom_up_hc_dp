#ifndef _HARVEST_H_
#define _HARVEST_H_

#include "health_state.h"

namespace healthcare {
class Harvest{
public:
  virtual int GetWorkingHarvest(const HealthState& state) const { return GetHarvest(state); }
  virtual bool InRange(int period) const = 0;
  virtual int GetHarvest(const HealthState& state) const {
    return InRange(state.period) ? CalculateHarvest(state) : 0;
  };
  Harvest() = default;
  Harvest(const Harvest&) = delete;
  Harvest& operator=(const Harvest&) = delete;
  virtual ~Harvest() {}
 protected:
  virtual int CalculateHarvest(const HealthState& state) const = 0;
};
} // namespace healthcare
#endif // _HARVEST_H_
