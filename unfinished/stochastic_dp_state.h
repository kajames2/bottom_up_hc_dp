#ifndef _STOCHASTIC_DP_STATE_H_
#define _STOCHASTIC_DP_STATE_H_

#include "dp_state.h"
#include <memory>

namespace genericdp {
template<class T> class StochasticDPState :
    public DPState<T> {
public:
  virtual std::unique_ptr<DPStateIterator<T>> GetExogenousStates() const = 0;
};

}  // namespace genericdp
#endif  // _STOCHASTIC_DP_STATE_H_
