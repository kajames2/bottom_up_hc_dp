#include "endogenous_result_iterator.h"
#include "health_state.h"
#include "investment.h"
#include "period_result.h"
#include "period_result_factory.h"

#include <algorithm>
#include <iostream>

namespace healthcaredp {
EndogenousResultIterator::EndogenousResultIterator(
    const ResultToEndogenousAdapterFactory& state_factory,
    const healthcare::HealthState &state, int max_remaining_cash)
    : state_factory_(state_factory)
    , invest_state_(state)
    , available_cash_(state.cash)
    , cur_investment_(0, 0)
    , prev_health_regained_(0)
    , max_remaining_cash_(max_remaining_cash) {
  cur_investment_.life_investment = available_cash_ - max_remaining_cash_;
  prev_health_regained_ = GetHealthRegained(cur_investment_);
  state_ = GetEndogenousResult();
}

EndogenousResultIterator &EndogenousResultIterator::operator++() {
  if (HasRemainingCash(cur_investment_)) {
    cur_investment_.life_investment += 1;
    state_ = GetEndogenousResult();
    return *this;
  }
  
  int next_health_investment = NextUniqueHealthInvestment();
  if (next_health_investment != -1) {
    cur_investment_.health_investment = next_health_investment;
    cur_investment_.life_investment =
        std::max(0, available_cash_ - cur_investment_.health_investment -
                        max_remaining_cash_);
    prev_health_regained_ = GetHealthRegained(cur_investment_);
    state_ = GetEndogenousResult();
    return *this;
  }

  done_ = true;
  return *this;
}

int EndogenousResultIterator::NextUniqueHealthInvestment() const {
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

int EndogenousResultIterator::GetHealthRegained(
    healthcare::Investment investment) const {
  return state_factory_.GetHealthRegained(invest_state_, investment);
}

bool EndogenousResultIterator::HasRemainingCash(
    healthcare::Investment investment) const {
  return investment.life_investment + investment.health_investment <
         available_cash_;
}

std::unique_ptr<ResultToEndogenousAdapter> EndogenousResultIterator::GetEndogenousResult() const {
  return state_factory_.GetEndogenousResult(invest_state_, cur_investment_);
}
} // namespace healthcaredp
