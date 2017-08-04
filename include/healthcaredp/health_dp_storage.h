#ifndef _HEALTH_DP_STORAGE_H_
#define _HEALTH_DP_STORAGE_H_

#include "dp_result.h"
#include "dp_storage.h"
#include "health_state.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
#include <vector>
#include <iostream>

namespace healthcaredp {
template <template <typename> class Container>
class HealthDPStorage
    : public genericdp::DPStorage<healthcare::HealthState, Container> {
public:
  HealthDPStorage(int max_periods, int max_remaining_cash);

  const Container<healthcare::HealthState> &
  GetOptimalResult(const healthcare::HealthState &state) const override;
  bool IsTerminalState(const healthcare::HealthState &state) const override;
  bool IsStoredState(const healthcare::HealthState &state) const override;
  double GetOptimalValue(const healthcare::HealthState &state) const override;
  void StoreOptimalResult(
      const healthcare::HealthState &state,
      Container<healthcare::HealthState> end_state) override;
  void StoreOptimalValue(const healthcare::HealthState &state,
                         double value) override;

private:
  int GetIndex(const healthcare::HealthState &state) const;
  std::vector<Container<healthcare::HealthState>> result_table_;
  std::vector<double> value_table_;
  std::vector<bool> is_stored_table_;
  
  int max_periods_;
  int max_remaining_cash_;
  const int sub_table_size_;
  const int row_size_;
};

template <template <typename> class Container>
HealthDPStorage<Container>::HealthDPStorage(int max_periods,
                                            int max_remaining_cash)
    : max_periods_(max_periods), max_remaining_cash_(max_remaining_cash),
      sub_table_size_((100 + 1) * (max_remaining_cash + 1)),
      row_size_(max_remaining_cash_ + 1) {
  result_table_.resize(max_periods * sub_table_size_);
  value_table_.resize(max_periods_ * sub_table_size_, 0);
  is_stored_table_.resize(max_periods_ * sub_table_size_, false);
}

template <template <typename> class Container>
bool HealthDPStorage<Container>::IsStoredState(
    const healthcare::HealthState &state) const {
  return is_stored_table_.at(GetIndex(state));
}

template <template <typename> class Container>
double HealthDPStorage<Container>::GetOptimalValue(
    const healthcare::HealthState &state) const {
  return value_table_.at(GetIndex(state));
}

template <template <typename> class Container>
const Container<healthcare::HealthState> &
HealthDPStorage<Container>::GetOptimalResult(
    const healthcare::HealthState &state) const {
  return result_table_.at(GetIndex(state));
}

template <template <typename> class Container>
bool HealthDPStorage<Container>::IsTerminalState(
    const healthcare::HealthState &state) const {
  return state.period > max_periods_ || !healthcare::IsAlive(state);
}

template <template <typename> class Container>
void HealthDPStorage<Container>::StoreOptimalResult(
    const healthcare::HealthState &state,
    Container<healthcare::HealthState> opt_result) {
  result_table_.at(GetIndex(state)) = std::move(opt_result);
  is_stored_table_.at(GetIndex(state)) = true;
}

template <template <typename> class Container>
void HealthDPStorage<Container>::StoreOptimalValue(
    const healthcare::HealthState &state, double value) {
  value_table_.at(GetIndex(state)) = value;
}

template <template <typename> class Container>
int HealthDPStorage<Container>::GetIndex(
    const healthcare::HealthState &state) const {
  return ((state.period - 1) * sub_table_size_) + (state.health * row_size_) +
         state.cash;
}

} // namespace healthcaredp
#endif // _HEALTH_DP_STORAGE_H_
