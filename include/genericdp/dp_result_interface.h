#ifndef _DP_RESULT_INTERFACE_H_
#define _DP_RESULT_INTERFACE_H_

#include "endogenous_state.h"
#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class DPResultInterface {
public:
  virtual std::unique_ptr<DPResultInterface> Clone() const = 0;
  virtual T GetState() const = 0;
  virtual std::string GetString() const = 0;
  virtual std::string GetHeader() const = 0;

  friend std::ostream &operator<<(std::ostream &out,
                                  const DPResultInterface &b) {
    out << b.GetString();
    return out;
  }

  virtual double GetValue() const = 0;

  DPResultInterface() = default;
  DPResultInterface(const DPResultInterface &) = delete;
  DPResultInterface &operator=(const DPResultInterface &) = delete;
  virtual ~DPResultInterface() {}
};
}

#endif // _DP_RESULT_INTERFACE_H_
