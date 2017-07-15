#ifndef _PERIOD_RESULT_ITERATOR_H_
#define _PERIOD_RESULT_ITERATOR_H_

#include "period_result.h"
#include "investment.h"
#include "period_result_factory.h"
#include "health_state.h"

#include <memory>

namespace healthcaredp {
class PeriodResultIterator
    : public genericdp::EndogenousIterator<PeriodResult> {
public:
  PeriodResultIterator(
      std::shared_ptr<const healthcare::PeriodResultFactory> state_factory,
      const ExogenousHealthState &state, int max_remaining_cash = 20);
  virtual PeriodResultIterator &operator++() override;

private:
  int NextUniqueHealthInvestment() const;
  bool HasRemainingCash(healthcare::Investment investment) const;
  healthcare::PeriodResult GetPeriodResult() const;
  int GetHealthRegained(healthcare::Investment investment) const;

  int available_cash_;
  int prev_health_regained_;
  const int max_remaining_cash_;
  healthcare::Investment cur_investment_;
  healthcare::HealthState invest_state_;
  std::shared_ptr<const healthcare::PeriodResultFactory> state_factory_;
};
} // namespace healthcaredp
#endif // _PERIOD_RESULT_ITERATOR_H_
