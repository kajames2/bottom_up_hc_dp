#ifndef _HEALTH_INVESTMENT_STATE_FACTORY_H_
#define _HEALTH_INVESTMENT_STATE_FACTORY_H_

#include "degeneration.h"
#include "harvest.h"
#include "health_state.h"

#include <memory>

namespace healthcare {
class HealthInvestmentStateFactory {
public:
  HealthInvestmentStateFactory(
      std::shared_ptr<const Harvest> harvest,
      std::shared_ptr<const Degeneration> degeneration);
  HealthState GetInvestmentState(const HealthState &state) const;
  int GetDegeneration(const HealthState &state) const;
  int GetHarvest(const HealthState &state) const;
  int GetWorkingHarvest(const HealthState &state) const;

private:
  int GetHealthAtInvestment(const HealthState &state) const;
  int GetCashAtInvestment(const HealthState &state) const;
  int GetTotalWorkingHarvest(const HealthState &state) const;

  std::shared_ptr<const Harvest> harvest_;
  std::shared_ptr<const Degeneration> degeneration_;
};
} // namespace healthcare
#endif // _HEALTH_INVESTMENT_STATE_FACTORY_H_
