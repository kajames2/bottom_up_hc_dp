#include "health_investment_state_factory.h"
#include "health_state.cc"

namespace healthcare {
HealthInvestmentStateFactory::HealthInvestmentStateFactory(
    const DegenerationStrategy *degeneration_strat,
    const HarvestStrategy *harvest_strat)
    : degeneration_strat_(degeneration_strat)
    , harvest_strat_(harvest_strat) {}

int HealthInvestmentStateFactory::GetNextHealth(
    const HealthState &state) const {
  return state.GetHealth() - GetDegenerationAmount(state);
}

int HealthInvestmentStateFactory::GetNextCash(const HealthState &state) const {
  return state.IsDead() ? 0 : state.GetCash() + GetHarvestAmount(state);
}

int HealthInvestmentStateFactory::GetHarvestAmount(
    const HealthState &state) const {
  return harvest_strat_->GetHarvest(state.GetPeriod() + 1, state.GetHealth(),
                                    state.GetTotalWorkingHarvest());
}

int HealthInvestmentStateFactory::GetDegenerationAmount(
    const HealthState &state) const {
  return degeneration_strat_->GetDegeneration(state.GetPeriod() + 1);
}

int HealthInvestmentStateFactory::GetNextTotalWorkingHarvest(
    const HealthState &state) const {
  return harvest_strat_->GetWorkingHarvest(
      state.GetPeriod() + 1, state.GetHealth(), state.GetTotalWorkingHarvest());
}

HealthState HealthInvestmentStateFactory::GetNextPeriodState(
    const HealthState &state) const {
  return HealthState(state.GetPeriod() + 1, GetNextHealth(state),
                     GetNextCash(state), GetNextTotalWorkingHarvest(state));
}
} // namespace healthcare
