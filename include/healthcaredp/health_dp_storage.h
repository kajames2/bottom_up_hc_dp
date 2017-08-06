#ifndef _HEALTH_DP_STORAGE_H_
#define _HEALTH_DP_STORAGE_H_

#include "dp_result.h"
#include "dp_storage.h"
#include "health_state.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace healthcaredp {
template <typename T>
class HealthDPStorage
    : public genericdp::DPStorage<healthcare::HealthState, T> {
public:
  HealthDPStorage(int max_periods, int max_remaining_cash);

  const T &
  GetOptimalResult(const healthcare::HealthState &state) const override;
  bool IsTerminalState(const healthcare::HealthState &state) const override;
  bool IsStoredState(const healthcare::HealthState &state) const override;
  double GetOptimalValue(const healthcare::HealthState &state) const override;
  void StoreOptimalResult(const healthcare::HealthState &state, T end_state,
                          double value) override;

private:
  bool IsValidState(const healthcare::HealthState &state) const;
  int GetIndex(const healthcare::HealthState &state) const;
  std::vector<T> result_table_;
  std::vector<double> value_table_;
  std::vector<bool> is_stored_table_;

  int max_periods_;
  int max_remaining_cash_;
  const int sub_table_size_;
  const int row_size_;
};

template <typename T>
HealthDPStorage<T>::HealthDPStorage(int max_periods, int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash),
      sub_table_size_((100 + 1) * (max_remaining_cash + 1)),
      row_size_(max_remaining_cash_ + 1) {
  result_table_.resize(max_periods * sub_table_size_);
  value_table_.resize(max_periods_ * sub_table_size_, 0);
  is_stored_table_.resize(max_periods_ * sub_table_size_, false);
}

template <typename T>
bool HealthDPStorage<T>::IsStoredState(
    const healthcare::HealthState &state) const {
  return is_stored_table_.at(GetIndex(state));
}

template <typename T>
double HealthDPStorage<T>::GetOptimalValue(
    const healthcare::HealthState &state) const {
  return value_table_.at(GetIndex(state));
}

template <typename T>
const T &HealthDPStorage<T>::GetOptimalResult(
    const healthcare::HealthState &state) const {
  return result_table_.at(GetIndex(state));
}

template <typename T>
bool HealthDPStorage<T>::IsTerminalState(
    const healthcare::HealthState &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

template <typename T>
void HealthDPStorage<T>::StoreOptimalResult(
    const healthcare::HealthState &state, T opt_result, double value) {
  result_table_.at(GetIndex(state)) = opt_result;
  value_table_.at(GetIndex(state)) = value;
  is_stored_table_.at(GetIndex(state)) = true;
}

template <typename T>
int HealthDPStorage<T>::GetIndex(const healthcare::HealthState &state) const {
  if (IsValidState(state)) {
    return ((state.period - 1) * sub_table_size_) + (state.health * row_size_) +
           state.cash;
  } else {
    throw std::out_of_range("HealthState out of range.");
  }
}

template <typename T>
bool HealthDPStorage<T>::IsValidState(
    const healthcare::HealthState &state) const {
  return state.period > 0 && state.period <= max_periods_ &&
         state.health >= 0 && state.health <= 100 && state.cash >= 0 &&
         state.cash <= max_remaining_cash_;
}

} // namespace healthcaredp
#endif // _HEALTH_DP_STORAGE_H_
