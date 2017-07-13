#ifndef _DP_STATE_H_
#define _DP_STATE_H_

#include "dp_state_iterator.h"
#include <memory>

namespace genericdp {
template<class T> class DPState {
 public:
  virtual bool SatisfiesEndCondition() const = 0;
  virtual double GetValue() const = 0;
  virtual std::unique_ptr<DPStateIterator<T>> GetEndogenousStates() const = 0;
  virtual bool operator <(const T&) const = 0;
};

}  // namespace genericdp
#endif  // _DP_STATE_H_
