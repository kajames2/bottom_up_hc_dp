#ifndef _ENDOGENOUS_FACTORY_H_
#define _ENDOGENOUS_FACTORY_H_

#include "endogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class EndogenousFactory {
public:
  virtual std::unique_ptr<EndogenousState<T>>
  GetEndogenous(const T &state) const = 0;

  EndogenousFactory() = default;
  EndogenousFactory(const EndogenousFactory<T> &) = delete;
  EndogenousFactory &operator=(const EndogenousFactory<T> &) = delete;
  virtual ~EndogenousFactory() {}
};
} // namespace genericdp
#endif // _ENDOGENOUS_FACTORY_H_
