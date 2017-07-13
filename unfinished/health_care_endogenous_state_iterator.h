#ifndef _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_H_
#define _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_H_

#include "dp_state_iterator.h"
#include "health_care_dp_state.h"
#include "health_end_state_factory.h"

namespace healthcaredp {
class HealthCareEndogenousStateIterator:
    public genericdp::DPStateIterator<HealthCareDPState> {
public:
  HealthCareEndogenousStateIterator(const HealthCareDPState& investment_state, const healthcare::HealthEndStateFactory *state_factory);
  genericdp::DPStateIterator<HealthCareDPState>& operator++() override;
 private:
  int available_cash_;
  int health_invest_;
  int life_invest_;
  int prev_health_regained_;
  const healthcare::HealthEndStateFactory *state_factory;
};
}  // namespace healthcaredp
#endif  // _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_H_
