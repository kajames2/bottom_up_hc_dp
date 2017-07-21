#ifndef _HEALTH_DP_STORAGE_H_
#define _HEALTH_DP_STORAGE_H_

#include "dp_storage.h"
#include "endogenous_state.h"
#include "health_state.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
#include <vector>

namespace healthcaredp {
class HealthDPStorage : public genericdp::DPStorage<healthcare::HealthState> {
public:
  template <class T> using vector3d = std::vector<std::vector<std::vector<T>>>;
  using HS = healthcare::HealthState;

  HealthDPStorage(int max_periods, int max_remaining_cash);
  virtual std::unique_ptr<
      const genericdp::EndogenousState<healthcare::HealthState>>
  GetOptimalDecision(const HS &state) const override;
  virtual double GetOptimalValue(const HS &state) const override;
  virtual bool IsTerminalState(const HS &state) const override;
  virtual void StoreOptimalDecision(
      const HS &state,
      std::unique_ptr<const genericdp::EndogenousState<HS>> end_state) override;
  virtual void StoreOptimalValue(const HS &state, double value) override;

private:
  template <class T> T& AccessIndex(vector3d<T> &vec, const HS &state);
  template <class T> const T &AccessIndex(const vector3d<T> &vec, const HS &state) const;  
  vector3d<std::unique_ptr<
      const genericdp::EndogenousState<healthcare::HealthState>>>
      state_table_;
  vector3d<double> value_table_;
  int max_periods_;
  int max_remaining_cash_;
};
} // namespace healthcaredp
#endif // _HEALTH_DP_STORAGE_H_
