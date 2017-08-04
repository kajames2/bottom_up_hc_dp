#ifndef _STOCHASTIC_EXOGENOUS_SET_FACTORY_H_
#define _STOCHASTIC_EXOGENOUS_SET_FACTORY_H_

#include "stochastic_exogenous_state.h"
#include <vector>

namespace genericdp {

template <typename T> class StochasticExogenousSetFactory {
public:
  virtual std::vector<std::unique_ptr<StochasticExogenousState<T>>>
  GetExogenousSet(const T &state) const;
};

} // namespace genericdp

#endif // _STOCHASTIC_EXOGENOUS_SET_FACTORY_H_
