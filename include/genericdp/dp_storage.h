#ifndef _DP_STORAGE_H_
#define _DP_STORAGE_H_

#include "dp_result.h"

#include <memory>

namespace genericdp {
template <class T> class DPStorage {
public:
  virtual const DPResultInterface<T>& GetOptimalResult(const T& state) const = 0;
  virtual bool IsTerminalState(const T& state) const = 0;
  virtual bool IsStoredState(const T& state) const = 0;
  virtual double GetOptimalValue(const T& state) const = 0;
  virtual void StoreOptimalResult(const T& state, std::unique_ptr<const DPResultInterface<T>> opt_result) = 0;

  DPStorage() = default;
  DPStorage(const DPStorage<T>&) = delete;
  DPStorage& operator=(const DPStorage&) = delete;
  virtual ~DPStorage() {}
};
} // namespace genericdp
#endif // _DP_STORAGE_H_
