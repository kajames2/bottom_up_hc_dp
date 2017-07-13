#include "health_end_state_factory.h"
#include "consumption_strategy.h"
#include "health_state.h"
#include "regeneration_strategy.h"

#include <algorithm>

namespace healthcare {
HealthEndStateFactory::HealthEndStateFactory(
    const RegenerationStrategy *regeneration_strat,
    const ConsumptionStrategy *consumption_strat)
    : regeneration_strat_(regeneration_strat)
    , consumption_strat_(consumption_strat) {}

int HealthEndStateFactory::GetHealthAtEnd(int health_investment) const {
  return std::min(GetHealthRegained(health_investment) + state_->GetHealth(),
                  100);
}

int HealthEndStateFactory::GetHealthRegained(int health_investment) const {
  if (state_->IsDead()) {
    return 0;
  } else {
    return regeneration_strat_->GetHealthRegained(health_investment);
  }
}

double HealthEndStateFactory::GetLifeEnjoyment(int health_investment,
                                               int life_investment) const {
  if (state_->IsDead()) {
    return 0;
  } else {
    return consumption_strat_->GetLifeEnjoyment(
        GetHealthAtEnd(health_investment), life_investment);
  }
}

int HealthEndStateFactory::GetCashAtEnd(int health_investment,
                                        int life_investment) const {
  if (state_->IsDead() || state_->GetCash() < 0) {
    return 0;
  } else {
    return state_->GetCash() - health_investment - life_investment;
  }
}

HealthState
HealthEndStateFactory::GetPostInvestmentState(int health_investment,
                                              int life_investment) const {
  HealthState post_state(*state_);
  post_state.SetHealth(GetHealthAtEnd(health_investment));
  post_state.SetCash(GetCashAtEnd(health_investment, life_investment));
  return post_state;
}
}
