#ifndef _DECISION_OPTIMIZER_H_
#define _DECISION_OPTIMIZER_H_

#include "dp_storage.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_state.h"
#include <memory>

namespace genericdp {
template <class T> class DecisionOptimizer {
public:
  DecisionOptimizer(std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
                    double discount_rate);
  std::pair<std::shared_ptr<const EndogenousState<T>>, double>
  FindOptimal(const ExogenousState<T> &int_state,
              const DPStorage<T> &storage) const;

private:
  double CalculateValue(const EndogenousState<T> &end_state,
                        const DPStorage<T> &storage) const;

  std::unique_ptr<const EndogenousIteratorFactory<T>> fact_;
  double discount_rate_;
};

template <class T>
DecisionOptimizer<T>::DecisionOptimizer(
    std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
    double discount_rate)
    : fact_(std::move(fact)), discount_rate_(discount_rate) {}

template <class T>
std::pair<std::shared_ptr<const EndogenousState<T>>, double>
DecisionOptimizer<T>::FindOptimal(const ExogenousState<T> &int_state,
                                  const DPStorage<T> &storage) const {
  EndogenousIterator<T> &end_it = *(fact_->GetIterator(int_state));
  std::shared_ptr<EndogenousState<T>> opt_state = end_it->Clone();
  double opt_value = CalculateValue(*end_it, storage);
  while (++end_it) {
    double cur_value = CalculateValue(*end_it, storage);
    if (cur_value > opt_value) {
      opt_state = end_it->Clone();
      opt_value = cur_value;
    }
  }
  return std::make_pair(opt_state, opt_value);
}

template <class T>
double DecisionOptimizer<T>::CalculateValue(const EndogenousState<T> &end_state,
                                            const DPStorage<T> &storage) const {
  return end_state.GetValue() +
         discount_rate_ * storage.GetOptimalValue(end_state.GetState());
}

} // namespace genericdp
#endif // _DECISION_SOLVER_H_
