#ifndef _LINEAR_HARVEST_H_
#define _LINEAR_HARVEST_H_

#include "harvest.h"
#include "health_state.h"

namespace healthcare {

class LinearHarvest : public Harvest {
 public:
  LinearHarvest(int first_period, int last_period, double harvest_rate);
  bool InRange(int period) const override;
 protected:
  int CalculateHarvest(const HealthState& state) const override;
 private:
  int first_period_;
  int last_period_;
  double harvest_rate_;
};

} // namespace healthcare
#endif // _LINEAR_HARVEST_H_
