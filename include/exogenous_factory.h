#ifndef _EXOGENOUS_FACTORY_H_
#define _EXOGENOUS_FACTORY_H_

#include "exogenous_state.h"

namespace genericdp {
template <class T> class ExogenousFactory {
public:
  virtual ExogenousState<T> GetExogenous(T state) = 0;
};
} // namespace genericdp
#endif // _EXOGENOUS_FACTORY_H_
