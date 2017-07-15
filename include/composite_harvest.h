#ifndef _COMPOSITE_HARVEST_H_
#define _COMPOSITE_HARVEST_H_

#include <memory>
#include <vector>

#include "harvest.h"
#include "health_state.h"
#include "null_harvest.h"

namespace healthcare {
class CompositeHarvest : public Harvest {
public:
  CompositeHarvest();
  CompositeHarvest(std::vector<std::shared_ptr<Harvest>> harvest_strats);
  int GetWorkingHarvest(const HealthState &state) const override;
  void AddHarvest(std::shared_ptr<const Harvest> harvest);
  bool InRange(int period) const override;

protected:
  int CalculateHarvest(const HealthState &state) const override;

private:
  std::shared_ptr<const Harvest> GetHarvestInRange(int period) const;

  std::vector<std::shared_ptr<const Harvest>> harvest_strats_;
  std::shared_ptr<NullHarvest> null_harvest_;
};
} // namespace healthcare
#endif // _COMPOSITE_HARVEST_H_
