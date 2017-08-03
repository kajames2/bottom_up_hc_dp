#ifndef _HEALTH_DP_STORAGE_H_
#define _HEALTH_DP_STORAGE_H_

#include "dp_result.h"
#include "dp_storage.h"
#include "health_state.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
#include <vector>

namespace healthcaredp {
class HealthDPStorage : public genericdp::DPStorage<healthcare::HealthState> {
public:
  template <class T> using vector3d = std::vector<std::vector<std::vector<T>>>;
  using ResultPtr = std::unique_ptr<
      const genericdp::DPResultInterface<healthcare::HealthState>>;

  HealthDPStorage(int max_periods, int max_remaining_cash);

  const genericdp::DPResultInterface<healthcare::HealthState> &
  GetOptimalResult(const healthcare::HealthState &state) const override;
  bool IsTerminalState(const healthcare::HealthState &state) const override;
  bool IsStoredState(const healthcare::HealthState &state) const override;
  double GetOptimalValue(const healthcare::HealthState &state) const override;
  void StoreOptimalResult(const healthcare::HealthState &state,
                          ResultPtr end_state) override;

private:
  int GetIndex(const healthcare::HealthState &state) const;
  std::vector<ResultPtr> result_table_;
  std::vector<double> value_table_;

  int max_periods_;
  int max_remaining_cash_;
  const int sub_table_size_;
  const int row_size_;
};

} // namespace healthcaredp
#endif // _HEALTH_DP_STORAGE_H_
