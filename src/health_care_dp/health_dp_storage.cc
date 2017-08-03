#include "health_dp_storage.h"
#include "endogenous_state.h"
#include "health_state.h"
#include <iostream>

namespace healthcaredp {
HealthDPStorage::HealthDPStorage(int max_periods, int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash)
    , sub_table_size_((100+1)*(max_remaining_cash + 1))
    , row_size_(max_remaining_cash_ + 1) {
   result_table_.resize(max_periods_);
   for (auto &vec : result_table_) {
     vec.resize(100 + 1);
     for (auto &subvec : vec) {
       subvec.resize(max_remaining_cash_ + 1);
     }
   }
   is_stored_table_.resize(max_periods_ * sub_table_size_, false);
   value_table_.resize(max_periods_ * sub_table_size_, 0);
}

bool HealthDPStorage::IsStoredState(const HS &state) const {
  return is_stored_table_.at((state.period-1) * sub_table_size_ + state.health * row_size_ + state.cash);
}

double HealthDPStorage::GetOptimalValue(const HS &state) const {
  return value_table_.at((state.period-1) * sub_table_size_ + state.health * row_size_ + state.cash);
}

const genericdp::DPResultInterface<healthcare::HealthState> &
HealthDPStorage::GetOptimalResult(const HS &state) const {
  return *AccessIndex(state);
}

bool HealthDPStorage::IsTerminalState(const HS &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

void HealthDPStorage::StoreOptimalResult(
    const HS &state,
    std::unique_ptr<const genericdp::DPResultInterface<HS>> opt_result) {
  value_table_.at((state.period-1) * sub_table_size_ + state.health * row_size_ + state.cash) = opt_result->GetValue();
  AccessIndex(state) = std::move(opt_result);
  is_stored_table_.at((state.period-1) * sub_table_size_ + state.health * row_size_ + state.cash) = true;
}

std::unique_ptr<const genericdp::DPResultInterface<healthcare::HealthState>> &
HealthDPStorage::AccessIndex(const healthcare::HealthState &state) {
  return result_table_.at(state.period - 1).at(state.health).at(state.cash);
}

const std::unique_ptr<
    const genericdp::DPResultInterface<healthcare::HealthState>> &
HealthDPStorage::AccessIndex(const healthcare::HealthState &state) const {
  return result_table_.at(state.period - 1).at(state.health).at(state.cash);
}
}
