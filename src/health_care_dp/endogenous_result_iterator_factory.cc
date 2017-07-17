#include "endogenous_result_iterator_factory.h"
#include "exogenous_state.h"
#include "health_state.h"
#include "period_result_factory.h"

#include <memory>

namespace healthcaredp {
EndogenousResultIteratorFactory::EndogenousResultIteratorFactory(
    std::shared_ptr<const healthcare::Regeneration> regen,
    std::shared_ptr<const healthcare::Consumption> consumption,
    int max_remaining_cash)
    : state_factory_(healthcare::PeriodResultFactory(regen, consumption)),
      max_remaining_cash_(max_remaining_cash) {}

EndogenousResultIteratorFactory::EndogenousResultIteratorFactory(
    const ResultToEndogenousAdapterFactory &state_factory,
    int max_remaining_cash)
    : state_factory_(state_factory), max_remaining_cash_(max_remaining_cash) {}

EndogenousResultIterator EndogenousResultIteratorFactory::GetEndogenousIterator(
    const genericdp::ExogenousState<healthcare::HealthState>& state) const {
  return EndogenousResultIterator(state_factory_, state.GetState(), max_remaining_cash_);
}
} // namespace healthcaredp
