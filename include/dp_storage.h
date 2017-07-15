#ifndef _DP_STORAGE_H_
#define _DP_STORAGE_H_

#include "endogenous_state.h"

namespace genericdp {
template <class T> class DPStorage {
public:
  virtual const EndogenousState<T>& GetOptimalDecision(const T& state) const = 0;
  virtual double GetOptimalValue(const T& state) const = 0;
  virtual bool isTerminalState(const T& state) const = 0;
  virtual void StoreOptimalDecision(const T& state, const EndogenousState<T>& end_state) = 0;
  virtual void StoreOptimalValue(const T& state, double value) = 0;
};
} // namespace genericdp
#endif // _DP_STORAGE_H_
