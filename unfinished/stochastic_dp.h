#ifndef _STOCHASTIC_DP_H_
#define _STOCHASTIC_DP_H_

#include "dp_state_iterator.h"

#include <memory>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
#include <ostream>

namespace genericdp {
template <class T> class StochasticDP {
 public:
  explicit StochasticDP(double);
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

template <class T> StochasticDP<T>::StochasticDP(double discount)
  : discount_rate_(discount) {}

template <class T> std::pair<std::vector<std::pair<T, double>>, double> StochasticDP<T>::GetOptimalTransitions(const T& current_state) {
  if (transitions_.find(current_state) == transitions_.end()) {
    std::vector<T> optimal_transitions = CalculateOptimalTransitions(current_state);
    std::vector<std::pair<T,double>> transition_values;
    for (T transition : optimal_transitions) {
      double trans_value = ExpectedValue(transition);
      transition_values.push_back(std::make_pair(transition, trans_value);
    }
    transitions_[current_state] = transition_values;
  }
  return transitions_[current_state];
}

template <class T> std::vector<std::pair<double, T>> StochasticDP<T>::CalculateOptimalTransitions(
    const T& current_state) {
  std::vector<T> opt_transitions;
  std::unique_ptr<DPStateIterator<T>> ex_it = current_state.GetExogenousStates();
  while (++*ex_it) {
    opt_transitions.push_back(CalculateOptimalEndogenous(**ex_it));
  return opt_transition;
}

template <class T> T StochasticDP<T>::CalculateOptimalEndogenous(const DPStateIterator<T>& ex_state) {
  double max_value = -1;
  std::unique_ptr<DPStateIterator<T>> end_it = (*ex_it)->GetEndogenousStates();
  while (++*end_it) {
    double value = ExpectationValue(**end_it);
    if (value > max_value) {
        max_value = value;
        opt_transition = **end_it;
    }
  }

}
  
template <class T> double StochasticDP<T>::ExpectedValue(const T& state) {
  if (state.SatisfiesEndCondition()) {
    return state.GetValue();
  }

  double future_value = GetOptimalTransition(state).second;
  return state.GetValue() + discount_rate_ * future_value;
}

template <class T> std::ostream& StochasticDP<T>::WriteDP(std::ostream& out, const T& init) {
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
#endif  // _STOCHASTIC_DP_H_
