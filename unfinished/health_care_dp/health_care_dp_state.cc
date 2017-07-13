#include "health_care_dp_state.h"
#include "dp_state_iterator.h"
#include "health_care_endogenous_state_iterator.h"
#include "health_care_config.h"

#include <memory>
#include <tuple>

namespace healthcaredp {
HealthCareDPState::HealthCareDPState(int period, int n_periods, const healthcare::RegenerationStrategy* regeneration_strat, bool has_retirement, healthcare::HealthCareState health_care_state)
    : period_(period)
    , regeneration_strat_(regeneration_strat)
    , health_care_state_(health_care_state)
    , n_periods_(n_periods)
    , has_retirement_(has_retirement) {}


bool HealthCareDPState::SatisfiesEndCondition() const {
  return (health_care_state_.IsDead() ||
          period_ >= n_periods_);
}

double HealthCareDPState::GetValue() const {
  return health_care_state_.GetLifeEnjoyment();
}

HealthCareDPState HealthCareDPState::GetExogenousState() const {
  healthcare::HealthCareState health_care_state_.GetNextHealthCareState();
  HealthCareDPState next_state(period+1, n_periods, rege
}

std::unique_ptr<genericdp::DPStateIterator<HealthCareDPState>> HealthCareDPState::GetEndogenousStates() const {
  HealthCareDPState temp_state(*this);
  auto end_it = std::make_unique<HealthCareEndogenousStateIterator>(temp_state, regeneration_strat_);
  return end_it;
}

bool HealthCareDPState::operator<(const HealthCareDPState& o) const {
  if (period_ != o.period_) {
    return period_ < o.period_;
  } else if (health_care_state_.GetHealthAtEnd() != o.health_care_state_.GetHealthAtEnd()) {
    return health_care_state_.GetHealthAtEnd() < o.health_care_state_.GetHealthAtEnd();
  } else if (health_care_state_.GetCashAtEnd() != o.health_care_state_.GetCashAtEnd() || !has_retirement_) {
    return health_care_state_.GetCashAtEnd() < o.health_care_state_.GetCashAtEnd();
  } else {
    return health_care_state_.GetTotalWorkingHarvestAtEnd() < o.health_care_state_.GetTotalWorkingHarvestAtEnd();
  }
}

std::string HealthCareDPState::GetHeader() const {
  return health_care_state_.GetHeader();
}

std::ostream& operator<<(std::ostream &output, const HealthCareDPState& state) {
  output << state.GetHealthCareState();

  return output;
}}  // namespace healthcaredp
