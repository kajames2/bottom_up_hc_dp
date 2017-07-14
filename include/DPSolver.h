#ifndef _DECISION_OPTIMIZER_H_
#define _DECISION_OPTIMIZER_H_

#include "endogenous_iterator_factory.h"
#include "future_value_strategy.h"
#include <memory>

namespace genericdp {
template <class Intermediate, class End> class DecisionSolver {
public:
  DecisionSolver(
      std::shared_ptr<const EndogenousIteratorFactory<Intermediate, End>> fact, double discount_rate);
  std::pair<End, double>
  FindOptimal(const Intermediate &int_state,
              const FutureValueStrategy &val_strategy) const;

  std::shared_ptr<const EndogenousIteratorFactory<Intermediate, End>> fact_;
  double discount_rate_;
};

template <class Intermediate, class End>
std::pair<End, double> DecisionSolver<Intermediate, End>::FindOptimal(
    const Intermediate &int_state,
    const FutureValueStrategy &val_strategy) const {
  EndogenousIterator<End> end_it = fact_->GetIterator(int_state);
  End opt_state = *end_it;
  double opt_value = CalculateValue(*end_it);
  while (++end_it) {
    double cur_value = CalculateValue(*end_it);
    if (cur_value > opt_value) {
      opt_state = *end_it;
      opt_value = cur_value;
    }
  }
  return std::make_pair(opt_state, opt_value);
}

template <class Intermediate, class End>
double
DecisionSolver<Intermediate, End>::CalculateValue(const End &end_state) const {
  return end_state.GetValue() + discount_rate_ * val_strategy.GetFutureValue(end_state)
}

} // namespace genericdp
#endif // _DECISION_SOLVER_H_
