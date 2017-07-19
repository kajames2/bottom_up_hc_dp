#ifndef _NULL_HARVEST_H_
#define _NULL_HARVEST_H_

#include "harvest.h"
#include "health_state.h"

namespace healthcare {
class NullHarvest : public Harvest {
public:
  bool InRange(int period) const override { return false; }
 protected:
  int CalculateHarvest(const HealthState& state) const override { return -1; }
};
} // namespace healthcare
#endif // _NULL_HARVEST_H_
