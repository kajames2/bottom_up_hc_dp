#include "period_result_factory.h"
#include "consumption.h"
#include "health_state.h"
#include "investment.h"
#include "period_result.h"
#include "regeneration.h"

#include <algorithm>
#include <memory>

namespace healthcare {
PeriodResultFactory::PeriodResultFactory(
    std::unique_ptr<const Regeneration> regeneration,
    std::unique_ptr<const Consumption> consumption)
    : regeneration_(std::move(regeneration)), consumption_(std::move(consumption)) {}

PeriodResult
PeriodResultFactory::GetPeriodResult(const HealthState &state,
                                     const Investment &investment) const {
  PeriodResult result =
      PeriodResult(GetPostInvestmentState(state, investment), investment,
                   GetLifeEnjoyment(state, investment));
  return result;
}

HealthState PeriodResultFactory::GetPostInvestmentState(
    const HealthState &state, const Investment &investment) const {
  HealthState end_state =
      HealthState(state.period + 1, GetHealthAtEnd(state, investment),
                  GetCashAtEnd(state, investment), state.total_working_harvest);
  return end_state;
}

double
PeriodResultFactory::GetLifeEnjoyment(const HealthState &state,
                                      const Investment &investment) const {
  if (!IsAlive(state)) {
    return 0;
  }
  return consumption_->GetLifeEnjoyment(investment.life_investment,
                                        GetHealthAtEnd(state, investment));
}

int PeriodResultFactory::GetHealthRegained(const HealthState &state,
                                           const Investment &investment) const {
  if (!IsAlive(state)) {
    return 0;
  }
  int regen = regeneration_->GetHealthRegained(investment.health_investment,
                                               state.health);
  return std::min(100 - state.health, regen);
}

int PeriodResultFactory::GetHealthAtEnd(const HealthState &state,
                                        const Investment &investment) const {
  if (!IsAlive(state)) {
    return 0;
  }
  return state.health + GetHealthRegained(state, investment);
}

int PeriodResultFactory::GetCashAtEnd(const HealthState &state,
                                      const Investment &investment) const {
  if (!IsAlive(state)) {
    return 0;
  }
  return state.cash - investment.health_investment - investment.life_investment;
}
} // namespace healthcare
