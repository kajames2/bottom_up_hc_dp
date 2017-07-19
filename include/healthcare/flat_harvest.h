#ifndef _FLAT_HARVEST_H_
#define _FLAT_HARVEST_H_

#include "harvest.h"
#include "health_state.h"

namespace healthcare {

class FlatHarvest : public Harvest {
public:
  FlatHarvest(int first_period, int last_period, int harvest)
      : first_period_(first_period), last_period_(last_period),
        harvest_(harvest) {}
  bool InRange(int period) const override {
    return period >= first_period_ && period <= last_period_;
  }

protected:
  int CalculateHarvest(const HealthState &state) const override {
    return harvest_;
  };

private:
  int first_period_;
  int last_period_;
  int harvest_;
};

} // namespace healthcare
#endif // _FLAT_HARVEST_H_
