#include "endogenous_health_state_iterator.h"
#include "health_state.h"
#include "investment.h"
#include "period_result.h"
#include "period_result_factory.h"

#include <algorithm>

namespace healthcaredp {
EndogenousHealthStateIterator::EndogenousHealthStateIterator(
    std::shared_ptr<const healthcare::EndogenousHealthStateFactory> result_factory,
    const ExogenousHealthState &state, int max_remaining_cash)
    : result_factory_(result_factory), invest_state_(state.GetState()),
      available_cash_(state.GetState().cash), cur_investment_(0, 0),
      prev_health_regained_(0), max_remaining_cash_(max_remaining_cash) {
  cur_investment_.life_investment = available_cash_ - max_remaining_cash_;
  prev_health_regained_ = GetHealthRegained(cur_investment_);
  *state_ = GetEndogenousHealthState();
}

EndogenousHealthStateIterator &EndogenousHealthStateIterator::operator++() {
  if (HasRemainingCash(cur_investment_)) {
    cur_investment_.life_investment += 1;
    *state_ = GetEndogenousHealthState();
    return *this;
  }

  int next_health_investment = NextUniqueHealthInvestment();
  if (next_health_investment != -1) {
    cur_investment_.health_investment = next_health_investment;
    cur_investment_.life_investment =
        std::max(0, available_cash_ - cur_investment_.health_investment -
                        max_remaining_cash_);
    prev_health_regained_ = GetHealthRegained(cur_investment_);
    *state_ = GetEndogenousHealthState();
    return *this;
  }

  done_ = true;
  return *this;
}

int EndogenousHealthStateIterator::NextUniqueHealthInvestment() const {
  healthcare::Investment investment(cur_investment_);
  while (investment.health_investment < available_cash_) {
    investment.health_investment += 1;
    int health_regained = GetHealthRegained(investment);
    if (health_regained != prev_health_regained_) {
      return investment.health_investment;
    }
   }
  return -1;
}

int EndogenousHealthStateIterator::GetHealthRegained(
    healthcare::Investment investment) const {
  return result_factory_->GetHealthRegained(invest_state_, investment);
}

bool EndogenousHealthStateIterator::HasRemainingCash(
    healthcare::Investment investment) const {
  return investment.life_investment + investment.health_investment <
         available_cash_;
}

healthcare::EndogenousHealthState EndogenousHealthStateIterator::GetEndogenousHealthState() const {
  return result_factory_->GetEndogenousHealthState(invest_state_, cur_investment_);
}
} // namespace healthcaredp
