#ifndef _ENDOGENOUS_PERIOD_RESULT_ITERATOR_H_
#define _ENDOGENOUS_PERIOD_RESULT_ITERATOR_H_

#include "endogenous_iterator.h"
#include "health_state.h"
#include "period_result.h"
#include "period_result_factory.h"

#include <memory>

namespace healthcaredp {
class EndogenousPeriodResultIterator
    : public genericdp::EndogenousIterator<healthcare::PeriodResult> {
public:
  EndogenousPeriodResultIterator(
      std::shared_ptr<const healthcare::PeriodResultFactory> result_factory,
      std::shared_ptr<const healthcare::HealthState> state,
      int max_remaining_cash = 20);
  genericdp::EndogenousIterator<healthcare::PeriodResult> &
  operator++() override;

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
#endif // _ENDOGENOUS_PERIOD_RESULT_ITERATOR_H_
