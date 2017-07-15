#ifndef _PERIOD_RESULT_ITERATOR_H_
#define _PERIOD_RESULT_ITERATOR_H_

#include "endogenous_health_state.h"
#include "exogenous_health_state.h"
#include "endogenous_iterator.h"
#include "health_state.h"
#include "period_result.h"
#include "period_result_factory.h"

#include <memory>

namespace healthcaredp {
class PeriodResultIterator
    : public genericdp::EndogenousIterator<EndogenousHealthState> {
public:
  PeriodResultIterator(
      std::shared_ptr<const healthcare::PeriodResultFactory> result_factory,
      std::shared_ptr<const ExogenousHealthState> state,
      int max_remaining_cash = 20);
  virtual PeriodResultIterator& operator++() override;

private:
  bool HasRemainingCash();
  healthcare::PeriodResult GetPeriodResult();
  int CurrentHealthRegained();

  int available_cash_;
  int prev_health_regained_;
  const int max_remaining_cash_;
  healthcare::Investment cur_investment_;
  std::shared_ptr<const healthcare::HealthState> invest_state_;
  std::shared_ptr<const healthcare::PeriodResultFactory> result_factory_;
};
} // namespace healthcaredp
#endif // _PERIOD_RESULT_ITERATOR_H_
