#ifndef _RETIREMENT_HARVEST_H_
#define _RETIREMENT_HARVEST_H_

#include "harvest.h"
#include "health_state.h"

namespace healthcare {
class RetirementHarvest : public Harvest {
public:
  RetirementHarvest(int first_period, double earning_frac);
  int GetWorkingHarvest(const HealthState &state) const override { return 0; }
  bool InRange(int period) const override;

protected:
  int CalculateHarvest(const HealthState &state) const override;

private:
  double earning_frac_;
  int first_period_;
};
} // namespace healthcare
#endif // _RETIREMENT_HARVEST_H_
