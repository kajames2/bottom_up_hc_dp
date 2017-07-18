#ifndef _EXOGENOUS_FACTORY_H_
#define _EXOGENOUS_FACTORY_H_

#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class ExogenousFactory {
public:
  virtual std::unique_ptr<ExogenousState<T>> GetExogenous(const T& state) const = 0;
};
} // namespace genericdp
#endif // _EXOGENOUS_FACTORY_H_
