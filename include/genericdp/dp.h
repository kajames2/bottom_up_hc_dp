#ifndef _DP_H_
#define _DP_H_

#include "dp_result.h"
#include "dp_result_interface.h"
#include "dp_storage.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_factory.h"
#include "state_iterator.h"
#include "value_strategy.h"

#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

namespace genericdp {
template <class T> class DP {
public:
  DP(std::unique_ptr<DPStorage<T>> storage,
     std::unique_ptr<const ExogenousFactory<T>> ex_fact,
     std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
     std::unique_ptr<const ValueStrategy<T>> calculator);
  std::vector<std::unique_ptr<DPResultInterface<T>>> GetSolution(const T &init_state);
  const DPResultInterface<T>& GetOptimalResult(const T &init_state);
  double GetOptimalValue(const T &init_state);
  void BottomUpTrain(StateIterator<T> &state_iterator);
  void TrainIfNecessary(const T &state);
  void Train(const T &state);
private:
  std::unique_ptr<DPResult<T>> CalculateOptimal(const ExogenousState<T> &int_state);

  std::unique_ptr<DPStorage<T>> storage_;
  std::unique_ptr<const ExogenousFactory<T>> ex_fact_;
  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  std::unique_ptr<const ValueStrategy<T>> calculator_;
};

template <class T>
DP<T>::DP(std::unique_ptr<DPStorage<T>> storage,
          std::unique_ptr<const ExogenousFactory<T>> ex_fact,
          std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
          std::unique_ptr<const ValueStrategy<T>> calculator)
    : storage_(std::move(storage)), ex_fact_(std::move(ex_fact)),
      fact_(std::move(fact)), calculator_(std::move(calculator)) {}

template <class T>
std::vector<std::unique_ptr<DPResultInterface<T>>> DP<T>::GetSolution(const T &init_state) {
  std::vector<std::unique_ptr<DPResultInterface<T>>> solution;
  T cur_state = init_state;
  try {
    while (!storage_->IsTerminalState(cur_state)) {
      const DPResultInterface<T>& result = GetOptimalResult(cur_state);
      solution.push_back(result.Clone());
      cur_state = result.GetState();
    }
  } catch (const std::out_of_range &oor) {
    std::cerr << "A state was out of range for storage." << std::endl
              << oor.what() << std::endl;
  }

  return solution;
}

template <class T> void DP<T>::BottomUpTrain(StateIterator<T> &state_iterator) {
  do {
    Train(*state_iterator);
  } while (++state_iterator);
}

template <class T> const DPResultInterface<T>& DP<T>::GetOptimalResult(const T &state) {
  TrainIfNecessary(state);
  return storage_->GetOptimalResult(state);
}

template <class T> double DP<T>::GetOptimalValue(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  TrainIfNecessary(state);
  return storage_->GetOptimalValue(state);
}


template <class T> void DP<T>::TrainIfNecessary(const T &state) {
  if (!storage_->IsStoredState(state)) {
    Train(state);
  }
}

template <class T> void DP<T>::Train(const T &state) {
    auto ex_state = ex_fact_->GetExogenous(state);
    auto opt_result = CalculateOptimal(*ex_state);
    storage_->StoreOptimalResult(state, std::move(opt_result));  
}

template <class T>
std::unique_ptr<DPResult<T>>
DP<T>::CalculateOptimal(const ExogenousState<T> &int_state) {
  auto end_it_ptr = fact_->GetIterator(int_state);
  EndogenousIterator<T> &end_it_ref = *end_it_ptr;
  std::unique_ptr<const EndogenousState<T>> opt_state = nullptr;
  double opt_value = -1;
  do {
    double cur_value = calculator_->CalculateValue(
        end_it_ref->GetValue(), GetOptimalValue(end_it_ref->GetState()));
    if (!opt_state || cur_value > opt_value) {
      opt_state = std::move(end_it_ref->Clone());
      opt_value = cur_value;
    }
  } while (++end_it_ref);
  return std::make_unique<DPResult<T>>(int_state.Clone(), std::move(opt_state), opt_value);
}

} // namespace genericdp
#endif // _DP_H_
