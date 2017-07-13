#ifndef _HEALTH_CARE_DP_STATE_H_
#define _HEALTH_CARE_DP_STATE_H_

#include <ostream>
#include <memory>
#include <string>

#include "dp_state_iterator.h"
#include "generic_dp_state.h"
#include "health_care_state.h"

namespace healthcaredp {
class HealthCareDPState : public genericdp::GenericDPState<HealthCareDPState> {
 public:
  HealthCareDPState();
  HealthCareDPState(int max_period, int period,
                    int start_health, int start_cash);
  bool SatisfiesEndCondition() const override;
  double GetValue() const override;
  HealthCareDPState GetExogenousState() const override;
  std::unique_ptr<genericdp::DPStateIterator<HealthCareDPState>> GetEndogenousStates() const override;
  bool operator<(const HealthCareDPState&) const override;
  healthcare::HealthCareState GetHealthCareState() const {return health_care_state_;}
  int GetMaxPeriod() const {return max_period_;}
  int GetPeriod() const {return period_;}
  int GetStartHealth() const {return start_health_;}
  int GetStartCash() const {return start_cash_;}
  std::string GetHeader() const ;
  friend std::ostream& operator<<(std::ostream&, const HealthCareDPState&);
  healthcare::HealthCareState health_care_state_;
private:
  int max_period_, period_, start_health_, start_cash_;
};
}  // namespace healthcaredp
#endif  // _HEALTH_CARE_DP_STATE_H_
