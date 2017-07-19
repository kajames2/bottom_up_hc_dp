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

std::string
ResultToEndogenousAdapter::GetHeader(std::string delimeter = ", ") const {
  return "Period" + delimeter
      + "Inv. Health" + delimeter
      + "Inv. Cash" + delimeter
      + "Health Expenditure" + delimeter
      + "Life Expenditure" + delimeter
      + "End Health" + delimeter
      + "End Cash" + delimeter
      + "Life Enjoyment";
}

std::string
ResultToEndogenousAdapter::GetString(std::string delimeter = ", ") const {
  healthcare::HealthState hstate = end_state_.state;
  healthcare::HealthState istate = end_state_.investment_state;
  return std::to_string(istate.period) + delimeter +
         std::to_string(istate.health) + delimeter +
         std::to_string(istate.cash) + delimeter +
         std::to_string(end_state_.investment.health_investment) + delimeter +
         std::to_string(end_state_.investment.life_investment) + delimeter +
         std::to_string(hstate.health) + delimeter +
         std::to_string(hstate.cash) + delimeter +
         std::to_string(end_state_.enjoyment);
}
}
