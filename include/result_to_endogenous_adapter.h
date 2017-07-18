#ifndef _RESULT_TO_ENDOGENOUS_ADAPTER_H_
#define _RESULT_TO_ENDOGENOUS_ADAPTER_H_

#include "endogenous_state.h"
#include "period_result.h"

#include <ostream>

namespace healthcaredp {
class ResultToEndogenousAdapter
    : public genericdp::EndogenousState<healthcare::HealthState> {
public:
  ResultToEndogenousAdapter(healthcare::PeriodResult end_state);
  virtual healthcare::HealthState GetState() const override;
  virtual double GetValue() const override;
  virtual std::unique_ptr<genericdp::EndogenousState<healthcare::HealthState>>
  Clone() const override;

private:
  virtual void Print(std::ostream &) const override;
  healthcare::PeriodResult end_state_;
};
} // namespace healthcaredp
#endif // _RESULT_TO_ENDOGENOUS_ADAPTER_H_
