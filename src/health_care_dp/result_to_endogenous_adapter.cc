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
  return std::make_unique<ResultToEndogenousAdapter>(end_state_);
}

std::string
ResultToEndogenousAdapter::GetHeader() const {
  return std::string("Period") + ", "
      + "Inv. Health" + ", "
      + "Inv. Cash" + ", "
      + "Health Expenditure" + ", "
      + "Life Expenditure" + ", "
      + "End Health" + ", "
      + "End Cash" + ", "
      + "Life Enjoyment";
}

std::string
ResultToEndogenousAdapter::GetString() const {
  healthcare::HealthState hstate = end_state_.state;
  healthcare::HealthState istate = end_state_.investment_state;
  return std::to_string(istate.period) + ", " +
         std::to_string(istate.health) + ", " +
         std::to_string(istate.cash) + ", " +
         std::to_string(end_state_.investment.health_investment) + ", " +
         std::to_string(end_state_.investment.life_investment) + ", " +
         std::to_string(hstate.health) + ", " +
         std::to_string(hstate.cash) + ", " +
         std::to_string(end_state_.enjoyment);
}
}
