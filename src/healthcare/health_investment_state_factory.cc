#include "health_investment_state_factory.h"
#include "health_state.h"

#include <algorithm>
#include <memory>

namespace healthcare {
HealthInvestmentStateFactory::HealthInvestmentStateFactory(
    std::shared_ptr<const Harvest> harvest,
    std::shared_ptr<const Degeneration> degeneration)
    : harvest_(harvest), degeneration_(degeneration) {}

HealthState HealthInvestmentStateFactory::GetInvestmentState(
    const HealthState &state) const {
  return HealthState(state.period, GetHealthAtInvestment(state),
                     GetCashAtInvestment(state), GetTotalWorkingHarvest(state));
}

int HealthInvestmentStateFactory::GetDegeneration(
    const HealthState &state) const {
  int degen = degeneration_->GetDegeneration(state.period);
  return std::min(degen, state.health);
}

int HealthInvestmentStateFactory::GetHarvest(const HealthState &state) const {
  return IsAlive(state) ? harvest_->GetHarvest(state) : 0;
}

int HealthInvestmentStateFactory::GetWorkingHarvest(
    const HealthState &state) const {
  return IsAlive(state) ? harvest_->GetWorkingHarvest(state) : 0;
}

int HealthInvestmentStateFactory::GetHealthAtInvestment(
    const HealthState &state) const {
  return IsAlive(state) ? state.health - GetDegeneration(state) : 0;
}

int HealthInvestmentStateFactory::GetCashAtInvestment(
    const HealthState &state) const {
  return GetHealthAtInvestment(state) > 0 ? state.cash + GetHarvest(state) : 0;
}

int HealthInvestmentStateFactory::GetTotalWorkingHarvest(
    const HealthState &state) const {
  return state.total_working_harvest + GetWorkingHarvest(state);
}
};
