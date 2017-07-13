#ifndef _HEALTH_CARE_DP_STATE_H_
#define _HEALTH_CARE_DP_STATE_H_

#include <ostream>
#include <memory>
#include <string>

#include "dp_state_iterator.h"
#include "deterministic_dp_state.h"
#include "health_state.h"

namespace healthcaredp {
class HealthCareDPState : public genericdp::DeterministicDPState<HealthCareDPState> {
 public:
  HealthCareDPState(int n_periods, healthcare::HealthState health_state);
  bool SatisfiesEndCondition() const override;
  double GetValue() const override;
  HealthCareDPState GetExogenousState() const override;
  std::unique_ptr<genericdp::DPStateIterator<HealthCareDPState>> GetEndogenousStates() const override;
  bool operator<(const HealthCareDPState&) const override;
  healthcare::HealthState GetHealthCareState() const {return health_state_;}
  std::string GetHeader() const;
  friend std::ostream& operator<<(std::ostream&, const HealthCareDPState&);

 private:
  int n_periods_;
  healthcare::HealthState health_state_;
};
}  // namespace healthcaredp
#endif  // _HEALTH_CARE_DP_STATE_H_
