#ifndef _EXOGENOUS_STRATEGY_H_
#define _EXOGENOUS_STRATEGY_H_

#include "exogenous_state.h"

namespace genericdp {
template <class T> class ExogenousStrategy {
public:
  virtual ExogenousState<T> GetExogenous(T state) = 0;
};
} // namespace genericdp
#endif // _EXOGENOUS_STRATEGY_H_
