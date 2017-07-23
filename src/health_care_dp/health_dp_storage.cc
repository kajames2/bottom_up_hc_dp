#include "health_dp_storage.h"
#include "endogenous_state.h"
#include "health_state.h"
#include <iostream>

namespace healthcaredp {
HealthDPStorage::HealthDPStorage(int max_periods, int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash) {
  value_table_.resize(max_periods_);
  for (auto &vec : value_table_) {
    vec.resize(100 + 1);
    for (auto &subvec : vec) {
      subvec.resize(max_remaining_cash_ + 1);
    }
  }

  state_table_.resize(max_periods_);
  for (auto &vec : state_table_) {
    vec.resize(100 + 1);
    for (auto &subvec : vec) {
      subvec.resize(max_remaining_cash_ + 1);
    }
  }
}

bool HealthDPStorage::IsStoredState(const HS &state) const {
  return static_cast<bool>(AccessIndex(state_table_, state));
}

const genericdp::EndogenousState<healthcare::HealthState>*
HealthDPStorage::GetOptimalDecision(const HS &state) const {
  return AccessIndex(state_table_, state).get();
}

double HealthDPStorage::GetOptimalValue(const HS &state) const {
  return AccessIndex(value_table_, state);
}

bool HealthDPStorage::IsTerminalState(const HS &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

void HealthDPStorage::StoreOptimalDecision(
    const HS &state,
    std::unique_ptr<const genericdp::EndogenousState<HS>> end_state) {
  AccessIndex(state_table_, state) = std::move(end_state);
}

void HealthDPStorage::StoreOptimalValue(const HS &state, double value) {
  AccessIndex(value_table_, state) = value;
}


template <class T>
T& HealthDPStorage::AccessIndex(vector3d<T> &vec,
                                const healthcare::HealthState &state) {
  return vec.at(state.period - 1).at(state.health).at(state.cash);
}

template <class T>
const T & HealthDPStorage::AccessIndex(const vector3d<T> &vec,
                             const healthcare::HealthState &state) const {
  return vec.at(state.period - 1).at(state.health).at(state.cash);
}
}
