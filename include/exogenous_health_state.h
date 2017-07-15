#ifndef _EXOGENOUS_HEALTH_STATE_H_
#define _EXOGENOUS_HEALTH_STATE_H_

#include "exogenous_state.h"
#include "health_state.h"

namespace healthcaredp {
class ExogenousHealthState
    : public genericdp::ExogenousState<healthcare::HealthState> {
public:
  ExogenousHealthState(healthcare::HealthState state) : state_(state) {}
  virtual healthcare::HealthState GetState() const override { return state_; }

private:
  healthcare::HealthState state_;
};
} // namespace healthcaredp
#endif // _EXOGENOUS_HEALTH_STATE_H_
