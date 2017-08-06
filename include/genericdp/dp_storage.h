#ifndef _DP_STORAGE_H_
#define _DP_STORAGE_H_

#include "dp_result.h"

#include <memory>

namespace genericdp {
template <typename Index, typename Result> class DPStorage {
public:
  virtual const Result &GetOptimalResult(const Index &state) const = 0;
  virtual bool IsTerminalState(const Index &state) const = 0;
  virtual bool IsStoredState(const Index &state) const = 0;
  virtual double GetOptimalValue(const Index &state) const = 0;
  virtual void StoreOptimalResult(const Index &state,
                                  Result opt_result) = 0;
  virtual void StoreOptimalValue(const Index &state, double value) = 0;

  DPStorage() = default;
  DPStorage(const DPStorage&) = delete;
  DPStorage &operator=(const DPStorage &) = delete;
  virtual ~DPStorage() {}
};
} // namespace genericdp
#endif // _DP_STORAGE_H_
