#ifndef _DECISION_OPTIMIZER_H_
#define _DECISION_OPTIMIZER_H_

#include "endogenous_iterator_factory.h"
#include "exogenous_state.h"
#include "endogenous_state.h"
#include "dp_storage.h"
#include <memory>

namespace genericdp {
template <class T> class DecisionOptimizer {
public:
  DecisionOptimizer(std::shared_ptr<const EndogenousIteratorFactory<T>> fact,
                 double discount_rate);
  std::pair<EndogenousState<T>, double>
  FindOptimal(const ExogenousState<T> &int_state,
              const DPStorage<T> &storage) const;

private:
  std::shared_ptr<const EndogenousIteratorFactory<T>> fact_;
  double CalculateValue(const EndogenousState<T> &end_state,
                        const DPStorage<T> &storage) const;
  double discount_rate_;
};

template <class T>
std::pair<EndogenousState<T>, double>
DecisionOptimizer<T>::FindOptimal(const ExogenousState<T> &int_state,
                               const DPStorage<T> &storage) const {
  EndogenousIterator<T> end_it = fact_->GetIterator(int_state);
  EndogenousState<T> opt_state = *end_it;
  double opt_value = CalculateValue(*end_it, storage);
  while (++end_it) {
    double cur_value = CalculateValue(*end_it, storage);
    if (cur_value > opt_value) {
      opt_state = *end_it;
      opt_value = cur_value;
    }
  }
  return std::make_pair(opt_state, opt_value);
}

template <class T>
double DecisionOptimizer<T>::CalculateValue(const EndogenousState<T> &end_state,
                                         const DPStorage<T> &storage) const {
  return end_state.value +
         discount_rate_ * storage.GetOptimalValue(end_state.state);
}

} // namespace genericdp
#endif // _DECISION_SOLVER_H_
