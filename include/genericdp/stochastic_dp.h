#ifndef _STOCHASTIC_DP_H_
#define _STOCHASTIC_DP_H_

#include "dp_storage.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_factory.h"
#include "stochastic_exogenous_state.h"
#include "state_iterator.h"
#include "stochastic_dp_result.h"
#include "stochastic_dp_result_set.h"
#include "value_strategy.h"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace genericdp {
template <class T> class StochasticDP {
public:
  StochasticDP(std::unique_ptr<DPStorage<StochasticDPResultSet<T>>> storage,
               std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact,
               std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
               std::unique_ptr<const ValueStrategy<T>> calculator);
  StochasticDPResultSet<T> GetSolution(const T &init_state);
  const StochasticDPResultSet<T> &TrainGetResult(const T &init_state);
  double TrainGetValue(const T &init_state);
  void BottomUpTrain(StateIterator<T> &state_iterator);

private:
  StochasticDPResult<T> FindOptimal(const ExogenousState<T> &int_state);

  std::unique_ptr<DPStorage<StochasticDPResultSet<T>>> storage_;
  std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact_;
  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  std::unique_ptr<const ValueStrategy<T>> calculator_;
};

template <class T>
StochasticDP<T>::StochasticDP(
    std::unique_ptr<DPStorage<StochasticDPResultSet<T>>> storage,
    std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact,
    std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
    std::unique_ptr<const ValueStrategy<T>> calculator)
    : storage_(std::move(storage)), ex_fact_(std::move(ex_fact)),
      fact_(std::move(fact)), calculator_(std::move(calculator)) {}

template <class T>
StochasticDPResultSet<T> StochasticDP<T>::GetSolution(const T &init_state) {
  StochasticDPResultSet<T> solution;
  try {
    StochasticDPResultSet<T> temp_sol = TrainGetResult(init_state);
    for (auto &result : temp_sol) {
      solution.AddResult(StochasticDPResult(result.exogenous_state.Clone(),
                                            result.endogenous_state.Clone(),
                                            result.value, result.probability));
    }
  } catch (const std::out_of_range &oor) {
    std::cerr << "A state was out of range for storage." << std::endl
              << oor.what() << std::endl;
  }

  return solution;
}

template <class T>
void StochasticDP<T>::BottomUpTrain(StateIterator<T> &state_iterator) {
  do {
    TrainGetValue(*state_iterator);
  } while (++state_iterator);
}

template <class T>
const StochasticDPResultSet<T> &StochasticDP<T>::TrainGetResult(const T &state) {
  if (!storage_->IsStoredState(state)) {
    StochasticDPResultSet<T> full_result;
    auto ex_state_set = ex_fact_->GetExogenousSet(state);
    for (auto& ex_state : ex_state_set) {
      auto opt_result = FindOptimal(*ex_state);
      full_result.AddResult(std::move(opt_result));
    }
    storage_->StoreOptimalResult(state, std::move(full_result));
  }
  return storage_->GetOptimalResult(state);
}

template <class T> double StochasticDP<T>::TrainGetValue(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  return TrainGetResult(state).GetValue();
}

template <class T>
StochasticDPResult<T> StochasticDP<T>::FindOptimal(const StochasticExogenousState<T> &int_state) {
  auto end_it_ptr = fact_->GetIterator(int_state);
  EndogenousIterator<T> &end_it_ref = *end_it_ptr;
  std::unique_ptr<const EndogenousState<T>> opt_state = nullptr;
  double opt_value = -1;
  do {
    double cur_value = calculator_->CalculateValue(
        end_it_ref->GetValue(), TrainGetValue(end_it_ref->GetState()));
    if (!opt_state || cur_value > opt_value) {
      opt_state = std::move(end_it_ref->Clone());
      opt_value = cur_value;
    }
  } while (++end_it_ref);
  return StochasticDPResult<T>(int_state.Clone(), std::move(opt_state), opt_value, int_state.GetProbability());
}

} // namespace genericdp
#endif // _STOCHASTIC_DP_H_
