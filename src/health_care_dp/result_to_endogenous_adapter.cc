#include "result_to_endogenous_adapter.h"

#include <memory>

namespace healthcaredp {
ResultToEndogenousAdapter::ResultToEndogenousAdapter(
    healthcare::PeriodResult end_state)
    : end_state_(end_state) {}

healthcare::HealthState ResultToEndogenousAdapter::GetState() const {
  return end_state_.state;
}

double ResultToEndogenousAdapter::GetValue() const {
  return end_state_.enjoyment;
}

std::unique_ptr<genericdp::EndogenousState<healthcare::HealthState>>
ResultToEndogenousAdapter::Clone() const {
  return std::make_unique<ResultToEndogenousAdapter>(*this);
}
}
