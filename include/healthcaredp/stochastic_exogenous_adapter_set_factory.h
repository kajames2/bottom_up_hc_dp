#ifndef _STOCHASTIC_EXOGENOUS_ADAPTER_SET_FACTORY_H_
#define _STOCHASTIC_EXOGENOUS_ADAPTER_SET_FACTORY_H_

#include "health_state.h"
#include "stochastic_exogenous_adapter_factory.h"
#include "stochastic_exogenous_set_factory.h"
#include <memory>
#include <vector>

namespace healthcaredp {
class StochasticExogenousAdapterSetFactory
    : public genericdp::StochasticExogenousSetFactory<healthcare::HealthState> {
public:
  using StochasticInvestmentState =
      genericdp::StochasticExogenousState<healthcare::HealthState>;
  StochasticExogenousAdapterSetFactory(
      std::vector<const healthcaredp::StochasticExogenousAdapterFactory> fact_set)
      : fact_set_(std::move(fact_set)) {}
  std::vector<StochasticInvestmentState>
  GetExogenousSet(const healthcare::HealthState &state) const override {
    std::vector<const StochasticInvestmentState &> state_set;
    for (auto &fact : fact_set_) {
      state_set.push_back(StochasticInvestmentState(fact.GetExogenous(state),
                                                    fact.GetProbability()));
    }
    return std::move(state_set);
  }

private:
  std::vector<const healthcaredp::StochasticExogenousAdapterFactory> fact_set_;
};
} // namespace healthcaredp

#endif // _STOCHASTIC_EXOGENOUS_ADAPTER_SET_FACTORY_H_
