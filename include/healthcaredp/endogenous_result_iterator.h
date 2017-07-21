#ifndef _ENDOGENOUS_RESULT_ITERATOR_H_
#define _ENDOGENOUS_RESULT_ITERATOR_H_

#include "endogenous_iterator.h"
#include "exogenous_state.h"
#include "health_state.h"
#include "investment.h"
#include "result_to_endogenous_adapter.h"
#include "result_to_endogenous_adapter_factory.h"

#include <memory>

namespace healthcaredp {
class EndogenousResultIterator
    : public genericdp::EndogenousIterator<healthcare::HealthState> {
public:
  EndogenousResultIterator(
      const ResultToEndogenousAdapterFactory& state_factory,
      const healthcare::HealthState &state,
      int max_remaining_cash = 0);
  virtual EndogenousResultIterator &operator++() override;
private:
  int NextUniqueHealthInvestment() const;
  bool HasRemainingCash(healthcare::Investment investment) const;
  std::unique_ptr<ResultToEndogenousAdapter> GetEndogenousResult() const;
  int GetHealthRegained(healthcare::Investment investment) const;

  int available_cash_;
  int prev_health_regained_;
  const int max_remaining_cash_;
  healthcare::Investment cur_investment_;
  healthcare::HealthState invest_state_;
  ResultToEndogenousAdapterFactory state_factory_;
};
} // namespace healthcaredp
#endif // _ENDOGENOUS_RESULT_ITERATOR_H_
