#ifndef _ENDOGENOUS_HEALTH_STATE_H_
#define _ENDOGENOUS_HEALTH_STATE_H_

#include "endogenous_state.h"
#include "period_result.h"

namespace healthcaredp {
class EndogenousHealthState
    : public genericdp::EndogenousState<healthcare::HealthState> {
public:
  EndogenousHealthState(healthcare::PeriodResult end_state)
      : end_state_(end_state) {}
  virtual healthcare::HealthState GetState() const override {
    return end_state_.state;
  }
  virtual double GetValue() const override { return end_state_.enjoyment; }

private:
  healthcare::PeriodResult end_state_;
};
} // namespace healthcaredp
#endif // _ENDOGENOUS_HEALTH_STATE_H_
