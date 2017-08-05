#ifndef _STOCHASTIC_EXOGENOUS_ADAPTER_FACTORY_H_
#define _STOCHASTIC_EXOGENOUS_ADAPTER_FACTORY_H_

#include "exogenous_state.h"
#include "health_state.h"
#include "health_state_to_exogenous_adapter_factory.h"

#include <memory>

namespace healthcaredp {
class StochasticExogenousAdapterFactory {
public:
  StochasticExogenousAdapterFactory() = default;
  StochasticExogenousAdapterFactory(
      std::unique_ptr<const HealthStateToExogenousAdapterFactory> fact, double prob)
      : fact_(std::move(fact)), probability_(prob) {}
  std::unique_ptr<genericdp::ExogenousState<healthcare::HealthState>>
  GetExogenous(const healthcare::HealthState &state) const {
    return fact_->GetExogenous(state);
  }
  double GetProbability() const { return probability_; }

private:
  std::unique_ptr<const HealthStateToExogenousAdapterFactory> fact_;
  double probability_;
};
} // namespace healthcare
#endif //  _STOCHASTIC_EXOGENOUS_ADAPTER_FACTORY_H_
