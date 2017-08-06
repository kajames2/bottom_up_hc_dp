#ifndef _HEALTH_DP_STORAGE_H_
#define _HEALTH_DP_STORAGE_H_

#include "dp_result.h"
#include "dp_storage.h"
#include "health_state.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
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
  void StoreOptimalResult(const healthcare::HealthState &state,
                          T end_state) override;
  void StoreOptimalValue(const healthcare::HealthState &state,
                         double value) override;

private:
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
    const healthcare::HealthState &state, T opt_result) {
  result_table_.at(GetIndex(state)) = opt_result;
  is_stored_table_.at(GetIndex(state)) = true;
}

template <typename T>
void HealthDPStorage<T>::StoreOptimalValue(const healthcare::HealthState &state,
                                           double value) {
  value_table_.at(GetIndex(state)) = value;
}

template <typename T>
int HealthDPStorage<T>::GetIndex(const healthcare::HealthState &state) const {
  return ((state.period - 1) * sub_table_size_) + (state.health * row_size_) +
         state.cash;
}

} // namespace healthcaredp
#endif // _HEALTH_DP_STORAGE_H_
