#include "result_to_endogenous_adapter_factory.h"
#include "period_result.h"
#include "period_result_factory.h"
#include "result_to_endogenous_adapter.h"

#include <memory>

namespace healthcaredp {
ResultToEndogenousAdapterFactory::ResultToEndogenousAdapterFactory(
    std::unique_ptr<healthcare::PeriodResultFactory> result_fact)
    : result_fact_(std::move(result_fact)) {}
std::unique_ptr<ResultToEndogenousAdapter>
ResultToEndogenousAdapterFactory::GetEndogenousResult(
    const healthcare::HealthState &state,
    const healthcare::Investment &investment) const {
  healthcare::PeriodResult result =
      result_fact_->GetPeriodResult(state, investment);
  return std::make_unique<ResultToEndogenousAdapter>(result);
}
} // namespace healthcaredp
