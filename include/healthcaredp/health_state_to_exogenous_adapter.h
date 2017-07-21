#ifndef _HEALTH_STATE_TO_EXOGENOUS_ADAPTER_H_
#define _HEALTH_STATE_TO_EXOGENOUS_ADAPTER_H_

#include "exogenous_state.h"
#include "health_state.h"

namespace healthcaredp {
class HealthStateToExogenousAdapter
    : public genericdp::ExogenousState<healthcare::HealthState> {
public:
  explicit HealthStateToExogenousAdapter(healthcare::HealthState state)
      : state_(state) {}
  virtual healthcare::HealthState GetState() const override { return state_; }

private:
  healthcare::HealthState state_;
};
} // namespace genericdp
#endif // _HEALTH_STATE_TO_EXOGENOUS_ADAPTER_H_
