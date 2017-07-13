#include "endogenous_period_result_iterator.h"
#include "health_state.h"
#include "period_result.h"
#include "period_result_factory.h"

#include <algorithm>

namespace healthcaredp {
EndogenousPeriodResultIterator::EndogenousPeriodResultIterator(
    std::shared_ptr<const healthcare::PeriodResultFactory> result_factory,
    std::shared_ptr<const healthcare::HealthState> state,
    int max_remaining_cash)
    : result_factory_(result_factory), invest_state_(state),
      available_cash_(state->cash), cur_investment_(0, 0),
      prev_health_regained_(0), max_remaining_cash_(max_remaining_cash) {
  cur_investment_.life_investment = available_cash_ - max_remaining_cash_;
  prev_health_regained_ = CurrentHealthRegained();
  state_ = GetPeriodResult();
}

genericdp::EndogenousIterator<healthcare::PeriodResult> &
    EndogenousPeriodResultIterator::operator++() {
  if (HasRemainingCash()) {
    cur_investment_.life_investment += 1;
    state_ = GetPeriodResult();
    return *this;
  }

  while (cur_investment_.health_investment < available_cash_) {
    cur_investment_.health_investment += 1;
    int health_regained = CurrentHealthRegained();
    if (health_regained != prev_health_regained_) {
      cur_investment_.life_investment =
          std::max(0, available_cash_ - cur_investment_.health_investment -
                          max_remaining_cash_);
      prev_health_regained_ = health_regained;
      state_ = GetPeriodResult();
      return *this;
    }
  }
  done_ = true;
  return *this;
}

int EndogenousPeriodResultIterator::CurrentHealthRegained() {
  return result_factory_->GetHealthRegained(*invest_state_, cur_investment_);
}

bool EndogenousPeriodResultIterator::HasRemainingCash() {
  return cur_investment_.life_investment + cur_investment_.health_investment <
         available_cash_;
}

healthcare::PeriodResult EndogenousPeriodResultIterator::GetPeriodResult() {
  return result_factory_->GetPeriodResult(*invest_state_, cur_investment_);
}
} // namespace healthcaredp