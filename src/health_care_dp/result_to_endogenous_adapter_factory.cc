#include "result_to_endogenous_adapter_factory.h"
#include "period_result.h"
#include "period_result_factory.h"
#include "result_to_endogenous_adapter.h"

#include <memory>

namespace healthcaredp {

ResultToEndogenousAdapterFactory::ResultToEndogenousAdapterFactory(
    healthcare::PeriodResultFactory result_fact)
    : result_fact_(result_fact) {}

std::unique_ptr<ResultToEndogenousAdapter> ResultToEndogenousAdapterFactory::GetEndogenousResult(
    const healthcare::HealthState &state,
    const healthcare::Investment &investment) const {
  healthcare::PeriodResult result =
      result_fact_.GetPeriodResult(state, investment);
  return std::make_unique<ResultToEndogenousAdapter>(result);
}

int ResultToEndogenousAdapterFactory::GetHealthRegained(
    const healthcare::HealthState &state,
    const healthcare::Investment &investment) const {
  return result_fact_.GetHealthRegained(state, investment);
}
} // namespace healthcaredp
