#ifndef _TOP_DOWN_DP_H_
#define _TOP_DOWN_DP_H_

#include "dp_storage.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_factory.h"

#include <memory>
#include <utility>
#include <vector>

namespace genericdp {
template <class T> class TopDownDP {
public:
  using StateValue =
      std::pair<std::shared_ptr<const EndogenousState<T>>, double>;

  TopDownDP(std::unique_ptr<DPStorage<T>> storage,
            std::unique_ptr<const ExogenousFactory<T>> ex_fact,
            std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
            double discount_rate);
  std::vector<StateValue> GetSolution(const T &init_state);
  StateValue TrainGet(const T &init_state);
private:
  std::pair<std::unique_ptr<const EndogenousState<T>>, double> FindOptimal(const ExogenousState<T> &int_state);
  double CalculateValue(const EndogenousState<T> &end_state);

  std::unique_ptr<DPStorage<T>> storage_;
  std::unique_ptr<const ExogenousFactory<T>> ex_fact_;
  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  double discount_rate_;
};

template <class T>
TopDownDP<T>::TopDownDP(
    std::unique_ptr<DPStorage<T>> storage,
    std::unique_ptr<const ExogenousFactory<T>> ex_fact,
    std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
    double discount_rate)
    : storage_(std::move(storage)), ex_fact_(std::move(ex_fact)),
      fact_(std::move(fact)), discount_rate_(discount_rate) {}

template <class T>
std::pair<std::shared_ptr<const EndogenousState<T>>, double>
TopDownDP<T>::TrainGet(const T &state) {
  if (storage_->IsTerminalState(state)) {
    return std::make_pair(nullptr, storage_->GetOptimalValue(state));
  }
  if (!storage_->GetOptimalDecision(state)) {
    auto ex_state = ex_fact_->GetExogenous(state);
    auto opt_state_value = FindOptimal(*ex_state);
    storage_->StoreOptimalDecision(state, std::move(opt_state_value.first));
    storage_->StoreOptimalValue(state, opt_state_value.second);
  }

  return std::make_pair(storage_->GetOptimalDecision(state), storage_->GetOptimalValue(state));
}

template <class T>
std::vector<std::pair<std::shared_ptr<const EndogenousState<T>>, double>>
TopDownDP<T>::GetSolution(const T &init_state) {
  std::vector<StateValue> solution;
  T cur_state = init_state;
  while (!storage_->IsTerminalState(cur_state)) {
    auto state_val = TrainGet(cur_state);
    solution.push_back(state_val);
    cur_state = state_val.first->GetState();
  }
  return solution;
}

template <class T>
std::pair<std::unique_ptr<const EndogenousState<T>>, double>
TopDownDP<T>::FindOptimal(const ExogenousState<T> &int_state) {
  auto end_it_ptr = fact_->GetIterator(int_state);
  EndogenousIterator<T> &end_it_ref = *end_it_ptr;
  auto opt_state = end_it_ref->Clone();
  double opt_value = CalculateValue(*end_it_ref);
  while (++end_it_ref) {
    double cur_value = CalculateValue(*end_it_ref);
    if (cur_value > opt_value) {
      opt_state = end_it_ref->Clone();
      opt_value = cur_value;
    }
  }
  return std::make_pair(std::move(opt_state), opt_value);
}

template <class T>
double TopDownDP<T>::CalculateValue(const EndogenousState<T> &end_state) {
  return end_state.GetValue() +
         discount_rate_ * TrainGet(end_state.GetState()).second;
}

} // namespace genericdp
#endif // _TOP_DOWN_DP_H_
