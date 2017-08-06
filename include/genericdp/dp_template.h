#ifndef _DP_TEMPLATE_H_
#define _DP_TEMPLATE_H_

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
#include <vector>

namespace genericdp {
template <typename T, typename Result> class DPTemplate {
public:
  DPTemplate(std::unique_ptr<DPStorage<T, Result>> storage,
             std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
             std::unique_ptr<const ValueStrategy<T>> calculator)
      : storage_(std::move(storage)), fact_(std::move(fact)),
        calculator_(std::move(calculator)) {}

  const Result& GetOptimalResult(const T &init_state);
  double GetOptimalValue(const T &init_state);
  void BottomUpTrain(StateIterator<T> &state_iterator);
  void TrainIfNecessary(const T &state);
  virtual void Train(const T &state) = 0;

protected:
  std::pair<std::unique_ptr<const EndogenousState<T>>, double>
  CalculateOptimal(const ExogenousState<T> &int_state);

  std::unique_ptr<DPStorage<T, Result>> storage_;
  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  std::unique_ptr<const ValueStrategy<T>> calculator_;
};

template <typename T, typename Result>
void DPTemplate<T, Result>::BottomUpTrain(StateIterator<T> &state_iterator) {
  do {
    Train(*state_iterator);
  } while (++state_iterator);
}

template <typename T, typename Result>
const Result &DPTemplate<T, Result>::GetOptimalResult(const T &state) {
  TrainIfNecessary(state);
  return storage_->GetOptimalResult(state);
}

template <typename T, typename Result>
double DPTemplate<T, Result>::GetOptimalValue(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return calculator_->CalculateTerminalValue(state);
  }
  TrainIfNecessary(state);
  return storage_->GetOptimalValue(state);
}

template <typename T, typename Result>
void DPTemplate<T, Result>::TrainIfNecessary(const T &state) {
  if (!storage_->IsStoredState(state)) {
    Train(state);
  }
}

template <typename T, typename Result>
std::pair<std::unique_ptr<const EndogenousState<T>>, double>
DPTemplate<T, Result>::CalculateOptimal(const ExogenousState<T> &int_state) {
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
  return std::make_pair(std::move(opt_state), opt_value);
}

} // namespace genericdp
#endif // _DP_TEMPLATE_H_
