#ifndef _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_FACTORY_H_
#define _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_FACTORY_H_

#include "dp_state_iterator.h"
#include "health_care_dp_state.h"
#include "health_care_config.h"
#include "regeneration_strategy.h"

namespace healthcaredp {
class HealthCareEndogenousStateIterator:
    public genericdp::DPStateIterator<HealthCareDPState> {
public:
  HealthCareEndogenousStateIterator(const HealthCareDPState& in_state, const healthcare::RegenerationStrategy* regeneration_strat);
  genericdp::DPStateIterator<HealthCareDPState>& operator++() override;
  int available_cash_;
  int health_invest_;
  int life_invest_;
  int prev_health_regained_;
  const healthcare::RegenerationStrategy* regeneration_strat_;
};
}  // namespace healthcaredp
#endif  // _HEALTH_CARE_ENDOGENOUS_STATE_ITERATOR_H_
