#include "endogenous_result_iterator_factory.h"
#include "flat_harvest.h"
#include "fractional_consumption.h"
#include "health_dp_storage.h"
#include "health_state_iterator.h"
#include "health_state_to_exogenous_adapter_factory.h"
#include "linear_degeneration.h"
#include "logistic_consumption.h"
#include "shifted_logistic_regeneration.h"
#include "dp.h"
#include "value_strategy.h"
#include "health_state_iterator.h"

#include <iostream>
#include <memory>
#include <utility>

int main() {
  int n_periods = 15;
  int max_remaining_cash = 20;
  auto harvest =
      std::make_shared<const healthcare::FlatHarvest>(1, n_periods, 100);
  auto degen = std::make_shared<const healthcare::LinearDegeneration>(0, 10);
  auto regen =
      std::make_shared<const healthcare::ShiftedLogisticRegeneration>(0.01021);
  auto consume = std::make_shared<const healthcare::FractionalConsumption>(32);

  auto ex_fact = std::make_unique<
      const healthcaredp::HealthStateToExogenousAdapterFactory>(harvest, degen);
  auto end_fact =
      std::make_unique<const healthcaredp::EndogenousResultIteratorFactory>(
          regen, consume, max_remaining_cash);

  auto storage = std::make_unique<healthcaredp::HealthDPStorage>(
      n_periods, max_remaining_cash);
  auto value_strat =
      std::make_unique<genericdp::ValueStrategy<healthcare::HealthState>>(1);

  genericdp::DP<healthcare::HealthState> health_dp(
      std::move(storage), std::move(ex_fact), std::move(end_fact),
      std::move(value_strat));

  //healthcaredp::HealthStateIterator state_it(n_periods, max_remaining_cash);
  //health_dp.BottomUpTrain(state_it);
  //std::cout << "finished training." << std::endl;
  auto solution = health_dp.GetSolution(healthcare::HealthState(1, 70, 0, 0));
  std::cout << solution[0].first->GetHeader() << ", "
            << "Total Value" << std::endl;
  for (auto &&end_state_value : solution) {
    std::cout << *end_state_value.first << ", " << end_state_value.second
              << std::endl;
  }
}
