#include "dp.h"
#include "dp_result.h"
#include "endogenous_result_iterator_factory.h"
#include "flat_harvest.h"
#include "fractional_consumption.h"
#include "health_dp_storage.h"
#include "health_state_iterator.h"
#include "health_state_iterator.h"
#include "health_state_to_exogenous_adapter_factory.h"
#include "linear_degeneration.h"
#include "logistic_consumption.h"
#include "shifted_logistic_regeneration.h"
#include "stochastic_dp.h"
#include "stochastic_exogenous_adapter_factory.h"
#include "stochastic_exogenous_adapter_set_factory.h"
#include "value_strategy.h"

#include <iostream>
#include <memory>
#include <utility>

int main() {
  int n_periods = 15;
  int max_remaining_cash = 150;
  auto regen =
      std::make_shared<const healthcare::ShiftedLogisticRegeneration>(0.01021);
  auto consume = std::make_shared<const healthcare::FractionalConsumption>(32);
  auto end_fact =
      std::make_unique<const healthcaredp::EndogenousResultIteratorFactory>(
          regen, consume, max_remaining_cash);

  auto harvest =
      std::make_shared<const healthcare::FlatHarvest>(1, n_periods, 100);
  auto degen = std::make_shared<const healthcare::LinearDegeneration>(0, 10);

  auto ex_fact = std::make_unique<
      const healthcaredp::HealthStateToExogenousAdapterFactory>(harvest, degen);

  auto value_strat =
      std::make_unique<genericdp::ValueStrategy<healthcare::HealthState>>(1);

  auto storage = std::make_unique<healthcaredp::HealthDPStorage<
      genericdp::DPResult<healthcare::HealthState>>>(n_periods,
                                                     max_remaining_cash);

  genericdp::DP<healthcare::HealthState> health_dp(
      std::move(storage), std::move(end_fact), std::move(value_strat),
      std::move(ex_fact));

  // healthcaredp::HealthStateIterator state_it(n_periods, max_remaining_cash);
  // health_dp.BottomUpTrain(state_it);
  auto solution = health_dp.GetSolution(healthcare::HealthState(1, 70, 0, 0));
  std::cout << solution[0].GetHeader() << std::endl;
  for (auto &opt_result : solution) {
    std::cout << opt_result.GetString() << std::endl;
  }

  // auto storage_stoch = std::make_unique<healthcaredp::HealthDPStorage<
  //     genericdp::StochasticDPResultSet<healthcare::HealthState>>>(
  //     n_periods, max_remaining_cash);

  // auto shock = std::make_shared<const healthcare::LinearDegeneration>(0, 45);

  // auto ex_fact2 = std::make_unique<
  //     const healthcaredp::HealthStateToExogenousAdapterFactory>(harvest,
  //     degen);
  // auto ex_fact_shock = std::make_unique<
  //     const healthcaredp::HealthStateToExogenousAdapterFactory>(harvest,
  //     shock);

  // healthcaredp::StochasticExogenousAdapterFactory stoch_fact(
  //     std::move(ex_fact2), 0.65);
  // healthcaredp::StochasticExogenousAdapterFactory stoch_shock_fact(
  //     std::move(ex_fact_shock), 0.35);

  // std::vector<healthcaredp::StochasticExogenousAdapterFactory> fact_set;
  // fact_set.push_back(std::move(stoch_fact));
  // fact_set.push_back(std::move(stoch_shock_fact));

  // auto ex_set_fact = std::make_unique<
  //     const healthcaredp::StochasticExogenousAdapterSetFactory>(
  //     std::move(fact_set));

  // genericdp::StochasticDP<healthcare::HealthState> health_dp(
  //     std::move(storage_stoch), std::move(end_fact), std::move(value_strat),
  //     std::move(ex_set_fact));

  // auto solution = health_dp.GetSolution(healthcare::HealthState(1, 70, 0,
  // 0));
  // std::cout << solution << std::endl;
}
