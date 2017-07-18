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

void ResultToEndogenousAdapter::Print(std::ostream &os) const {
  healthcare::HealthState hstate = end_state_.state;
  os << end_state_.investment.health_investment << ", "
     << end_state_.investment.life_investment << ", " << hstate.period << ", "
     << hstate.health << ", " << hstate.cash << ", " << end_state_.enjoyment;
}
}
