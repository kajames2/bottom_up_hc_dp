#ifndef _STOCHASTIC_EXOGENOUS_STATE_H_
#define _STOCHASTIC_EXOGENOUS_STATE_H_

#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class StochasticExogenousState {
public:
  StochasticExogenousState(std::unique_ptr<ExogenousState<T>> state, double prob)
      : state_(std::move(state)), probability_(prob) {}
  double GetProbability() const { return probability_; }
  ExogenousState<T>* GetExogenousState() const {return state_.get();}
private:
  std::unique_ptr<ExogenousState<T>> state_;
  double probability_;
};
} // namespace genericdp
#endif // _STOCHASTIC_EXOGENOUS_STATE_H_
