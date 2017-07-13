#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "generic_dp.h"
#include "health_care_dp_state.h"
#include "linear_harvest_strategy.h"
#include "tiered_harvest_strategy.h"
#include "linear_degeneration_strategy.h"
#include "logrithmic_regeneration_strategy.h"
#include "logrithmic_consumption_strategy.h"
#include "fractional_retirement_strategy.h"

using genericdp::GenericDP;
using healthcaredp::HealthCareDPState;

int main() {
  std::string filename = "22110_9.csv";
  int param_periods = 9;
  int n_periods = 9;
  bool tiered = false;
  int first_tier2_period = 4;

  bool retirement = true;
  int first_retirement_period = 7;

  int start_health = 100;
  // int start_health = 93;

  healthcare::LinearDegenerationStrategy degen(param_periods);
  healthcare::LogrithmicRegenerationStrategy regen(param_periods);
  healthcare::LogrithmicConsumptionStrategy consumption(param_periods);
  healthcare::FractionalRetirementStrategy retire(0.75, first_retirement_period);

  healthcare::LinearHarvestStrategy harvest1(5.914, param_periods);
  healthcare::LinearHarvestStrategy harvest2(14.57, param_periods);
  healthcare::TieredHarvestStrategy tier_harvest(&harvest1, &harvest2, first_tier2_period);
  healthcare::LinearHarvestStrategy flat_harvest(8.426, param_periods);
  healthcare::HarvestStrategy* harvest_strat;

  if (tiered) {
    harvest_strat = &tier_harvest;
  } else {
    harvest_strat = &flat_harvest;
  }
    
  int start_period = 0;
  int start_cash = -1000;

  GenericDP<HealthCareDPState> health_care_dp(1);
  healthcare::HealthCareState init_health_care_state(start_period, start_health, start_cash, 0, &degen, &regen, &retire, harvest_strat, &consumption, retirement, first_retirement_period);

  HealthCareDPState init_state(start_period, n_periods, &regen, retirement, init_health_care_state);
  std::cout << init_state.GetExogenousState() << std::endl;
  std::unique_ptr<genericdp::DPStateIterator<HealthCareDPState>> end_it = init_state.GetEndogenousStates();
  while(*end_it) {
    std::cout << **end_it << std::endl;
    ++(*end_it);
  }
  std::cout << init_state.SatisfiesEndCondition() << std::endl;

  healthcaredp::HealthCareDPState dp_state = init_state;

  std::ofstream outfile;
  outfile.open (filename);
  health_care_dp.WriteDP(outfile, init_state);
  outfile.close();

  return 0;
}
