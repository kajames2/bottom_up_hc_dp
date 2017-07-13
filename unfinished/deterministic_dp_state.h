#ifndef _DETERMINISTIC_DP_STATE_H_
#define _DETERMINISTIC_DP_STATE_H_

#include "dp_state.h"

namespace genericdp {
template<class T> class DeterministicDPState :
    public DPState<T> {
public:
  virtual T GetExogenousState() const = 0;
};

}  // namespace genericdp
#endif  // _DETERMINISTIC_DP_STATE_H_
