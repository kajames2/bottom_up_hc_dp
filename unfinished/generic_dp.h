#ifndef _GENERIC_DP_H_
#define _GENERIC_DP_H_

#include "dp_state_iterator.h"

#include <memory>
#include <algorithm>
#include <map>
#include <utility>
#include <ostream>

namespace genericdp {
template <class T> class GenericDP {
 public:
  explicit GenericDP(double);
  std::pair<T, double> GetOptimalTransition(const T&);
  double TotalValue(const T&);
  std::map<T, std::pair<T, double> > GetTransitions() {return transitions_;}
  T CalculateOptimalTransition(const T&);
  std::ostream& WriteDP(std::ostream& out, const T& init);
 private:
  bool CompareState(const T, const T);
  double discount_rate_;
  std::map<T, std::pair<T, double> > transitions_;
};

template <class T> GenericDP<T>::GenericDP(double discount)
  : discount_rate_(discount) {}

template <class T> std::pair<T, double> GenericDP<T>::GetOptimalTransition(const T& current_state) {
  if (transitions_.find(current_state) == transitions_.end()) {
    T optimal_transition = CalculateOptimalTransition(current_state);
    std::pair<T, double> transition_value = std::make_pair(
        optimal_transition, TotalValue(optimal_transition));
    transitions_.emplace(current_state, transition_value);
  }
  return transitions_.at(current_state);
}

template <class T> T GenericDP<T>::CalculateOptimalTransition(
    const T& current_state) {
  double max_value = -1;
  std::unique_ptr<DPStateIterator<T>> end_it = current_state.GetExogenousState().GetEndogenousStates();
  T opt_transition(**end_it);
  while (++*end_it) {
    double value = TotalValue(**end_it);
    if (value > max_value) {
      max_value = value;
      T opt_transition = **end_it;
    }
  }
  return opt_transition;
}

template <class T> double GenericDP<T>::TotalValue(const T& state) {
  if (state.SatisfiesEndCondition()) {
    return state.GetValue();
  }

  double future_value = GetOptimalTransition(state).second;
  return state.GetValue() + discount_rate_ * future_value;
}

template <class T> std::ostream& GenericDP<T>::WriteDP(std::ostream& out, const T& init) {
  out << init.GetHeader() << ", Total Value" << std::endl;
  auto dp_state = init;
  while (!dp_state.SatisfiesEndCondition()) {
    auto optimal_transition = GetOptimalTransition(dp_state);
    out << optimal_transition.first << ", " << optimal_transition.second << std::endl;
    dp_state = optimal_transition.first;
  }
  return out;
}

}  // namespace genericdp
#endif  // _GENERIC_DP_H_
