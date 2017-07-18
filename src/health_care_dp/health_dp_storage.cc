#include "health_dp_storage.h"
#include "endogenous_state.h"
#include "health_state.h"

namespace healthcaredp {
HealthDPStorage::HealthDPStorage(int max_periods, int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash) {
  value_table_.resize(max_periods_);
  for (auto& vec : value_table_) {
    vec.resize(100 + 1);
    for (auto& subvec : vec) {
      subvec.resize(max_remaining_cash_ + 1);
    }
  }
  
  state_table_.resize(max_periods_);
  for (auto& vec : state_table_) {
    vec.resize(100 + 1);
    for (auto& subvec : vec) {
      subvec.resize(max_remaining_cash_ + 1);
    }
  }
}

std::shared_ptr<const genericdp::EndogenousState<healthcare::HealthState>>
HealthDPStorage::GetOptimalDecision(const HS &state) const {
  return state_table_[state.period-1][state.health][state.cash];
}

double HealthDPStorage::GetOptimalValue(const HS &state) const {
  if (IsTerminalState(state)) {
    return 0;
  }
  return value_table_[state.period-1][state.health][state.cash];
}

bool HealthDPStorage::IsTerminalState(const HS &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

void HealthDPStorage::StoreOptimalDecision(
    const HS &state, std::unique_ptr<const genericdp::EndogenousState<HS>> end_state) {
  state_table_[state.period-1][state.health][state.cash] = std::move(end_state);
}

void HealthDPStorage::StoreOptimalValue(const HS &state, double value) {
  value_table_[state.period-1][state.health][state.cash] = value;
}
}
