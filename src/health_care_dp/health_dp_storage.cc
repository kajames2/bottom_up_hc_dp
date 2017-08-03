#include "health_dp_storage.h"
#include "health_state.h"
#include "dp_result_interface.h"

#include <memory>

namespace healthcaredp {
using healthcare::HealthState;

HealthDPStorage::HealthDPStorage(int max_periods, int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash),
      sub_table_size_((100 + 1) * (max_remaining_cash + 1)),
      row_size_(max_remaining_cash_ + 1) {
  result_table_.resize(max_periods * sub_table_size_);
  value_table_.resize(max_periods_ * sub_table_size_, 0);
}

bool HealthDPStorage::IsStoredState(const HealthState &state) const {
  return static_cast<bool>(result_table_.at(GetIndex(state)));
}

double HealthDPStorage::GetOptimalValue(const HealthState &state) const {
  return value_table_.at(GetIndex(state));
}

const genericdp::DPResultInterface<HealthState> &
HealthDPStorage::GetOptimalResult(const HealthState &state) const {
  return *result_table_.at(GetIndex(state));
}

bool HealthDPStorage::IsTerminalState(const HealthState &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

void HealthDPStorage::StoreOptimalResult(const HealthState &state,
                                         ResultPtr opt_result) {
  value_table_.at(GetIndex(state)) = opt_result->GetValue();
  result_table_.at(GetIndex(state)) = std::move(opt_result);
}

int HealthDPStorage::GetIndex(const HealthState &state) const {
  return ((state.period - 1) * sub_table_size_)
      + (state.health * row_size_)
      + state.cash;
}
}  // namespace healthcaredp
