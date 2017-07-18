#include "decision_optimizer.h"
#include "dp.h"
#include "endogenous_result_iterator_factory.h"
#include "linear_harvest.h"
#include "health_dp_storage.h"
#include "health_state_iterator.h"
#include "health_state_to_exogenous_adapter_factory.h"
#include "increasing_decay_consumption.h"
#include "linear_degeneration.h"
#include "logistic_regeneration.h"

#include <memory>
#include <iostream>

int main() {
  int n_periods = 18;
  int max_remaining_cash = 10;
  auto harvest =
      std::make_shared<const healthcare::LinearHarvest>(1, n_periods, 0.91);
  auto degen = std::make_shared<const healthcare::LinearDegeneration>(1, 15);
  auto regen =
      std::make_shared<const healthcare::LogisticRegeneration>(60, 0.025, 0);
  auto consume = std::make_shared<const healthcare::IncreasingDecayConsumption>(
      0.028, 500, 0.5);

  std::unique_ptr<const genericdp::ExogenousFactory<healthcare::HealthState>>
      ex_fact = std::make_unique<
          const healthcaredp::HealthStateToExogenousAdapterFactory>(harvest,
                                                                    degen);
  std::unique_ptr<const healthcaredp::EndogenousResultIteratorFactory> end_fact =
      std::make_unique<const healthcaredp::EndogenousResultIteratorFactory>(
          regen, consume);
  
  std::unique_ptr<genericdp::DPStorage<healthcare::HealthState>> storage =
      std::make_unique<healthcaredp::HealthDPStorage>(n_periods,
                                                      max_remaining_cash);

  genericdp::DecisionOptimizer<healthcare::HealthState> dec_opt(
      std::move(end_fact), 1);

  healthcaredp::HealthStateIterator state_it(n_periods, max_remaining_cash);

  genericdp::DP<healthcare::HealthState> health_dp(std::move(storage),
                                                   std::move(ex_fact),
                                                   dec_opt);

  health_dp.Train(state_it);
  auto solution = health_dp.GetSolution(healthcare::HealthState(1,100,0,0));
  for (auto end_state : solution) {
    std::cout << *end_state << std::endl;
  }
}
