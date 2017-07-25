#ifndef _DP_H_
#define _DP_H_

#include "dp_storage.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_factory.h"
#include "value_strategy.h"
#include "state_iterator.h"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace genericdp {
template <class T> class DP {
public:
  using DPResult = std::pair<std::unique_ptr<EndogenousState<T>>, double>;
  DP(std::unique_ptr<DPStorage<T>> storage,
            std::unique_ptr<const ExogenousFactory<T>> ex_fact,
            std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
            std::unique_ptr<const ValueStrategy<T>> calculator);
  std::vector<DPResult> GetSolution(const T &init_state);
  std::pair<const EndogenousState<T> *, double> TrainGet(const T &init_state);
  void BottomUpTrain(StateIterator<T>& state_iterator);

private:
  std::pair<std::unique_ptr<const EndogenousState<T>>, double> FindOptimal(const ExogenousState<T> &int_state);

  std::unique_ptr<DPStorage<T>> storage_;
  std::unique_ptr<const ExogenousFactory<T>> ex_fact_;
  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  std::unique_ptr<const ValueStrategy<T>> calculator_;
};

template <class T>
DP<T>::DP(
    std::unique_ptr<DPStorage<T>> storage,
    std::unique_ptr<const ExogenousFactory<T>> ex_fact,
    std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
    std::unique_ptr<const ValueStrategy<T>> calculator)
    : storage_(std::move(storage)), ex_fact_(std::move(ex_fact)),
      fact_(std::move(fact)), calculator_(std::move(calculator)) {}

template <class T>
std::vector<typename DP<T>::DPResult>
DP<T>::GetSolution(const T &init_state) {
  std::vector<DPResult> solution;
  T cur_state = init_state;
  try {
    while (!storage_->IsTerminalState(cur_state)) {
      auto state_val = TrainGet(cur_state);
      solution.push_back(
          std::make_pair(state_val.first->Clone(), state_val.second));
      cur_state = state_val.first->GetState();
    }
  } catch (const std::out_of_range &oor) {
    std::cerr << "A state was out of range for storage." << std::endl
              << oor.what() << std::endl;
  }

  return solution;
}

template <class T>
void DP<T>::BottomUpTrain(StateIterator<T>& state_iterator) {
  do {
    TrainGet(*state_iterator);
  } while (++state_iterator);
}

template <class T>
std::pair<const EndogenousState<T> *, double>
DP<T>::TrainGet(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return std::make_pair(nullptr, calculator_->CalculateTerminalValue(state));
  }
  if (!storage_->IsStoredState(state)) {
    auto ex_state = ex_fact_->GetExogenous(state);
    auto opt_state_value = FindOptimal(*ex_state);
    storage_->StoreOptimalDecision(state, std::move(opt_state_value.first));
    storage_->StoreOptimalValue(state, opt_state_value.second);
  }

  return std::make_pair(storage_->GetOptimalDecision(state),
                        storage_->GetOptimalValue(state));
}

template <class T>
std::pair<std::unique_ptr<const EndogenousState<T>>, double>
DP<T>::FindOptimal(const ExogenousState<T> &int_state) {
  auto end_it_ptr = fact_->GetIterator(int_state);
  EndogenousIterator<T> &end_it_ref = *end_it_ptr;
  std::unique_ptr<const EndogenousState<T>> opt_state = nullptr;
  double opt_value = -1;
  do {
    double cur_value = calculator_->CalculateValue(
        end_it_ref->GetValue(), TrainGet(end_it_ref->GetState()).second);
    if (!opt_state || cur_value > opt_value) {
      opt_state = std::move(end_it_ref->Clone());
      opt_value = cur_value;
    }
  } while (++end_it_ref);
  return std::make_pair(std::move(opt_state), opt_value);
}

} // namespace genericdp
#endif // _DP_H_
