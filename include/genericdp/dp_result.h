#ifndef _DP_RESULT_H_
#define _DP_RESULT_H_

#include "dp_result_interface.h"
#include "endogenous_state.h"
#include "exogenous_state.h"

#include <memory>
#include <iostream>

namespace genericdp {
template <class T> class DPResult {
public:
  DPResult(std::unique_ptr<const ExogenousState<T>> ex,
           std::unique_ptr<const EndogenousState<T>> end, double val)
      : exogenous_state_(std::move(ex)), endogenous_state_(std::move(end)),
        value_(val) {}
  DPResult()
      : exogenous_state_(nullptr), endogenous_state_(nullptr), value_(-1) {}

  DPResult(const DPResult &other)
      : exogenous_state_(other.exogenous_state_->Clone()),
        endogenous_state_(other.endogenous_state_->Clone()),
        value_(other.value_) {}
  DPResult &operator=(const DPResult &other) {
    if (&other == this) {
      return this;
    }
    DPResult copy = DPResult(other);
    using std::swap;
    swap(*this, copy);
    return *this;
  }
  DPResult(DPResult &&) = default;
  DPResult &operator=(DPResult &&) = default;

  std::string GetString() const {
    return exogenous_state_->GetString() + ", " +
           endogenous_state_->GetString() + ", " + std::to_string(GetValue());
  }

  std::string GetHeader() const {
    return exogenous_state_->GetHeader() + ", " +
           endogenous_state_->GetHeader() + ", " + "Value";
  }

  T GetState() const { return endogenous_state_->GetState(); }

  double GetValue() const { return value_; }
  std::unique_ptr<const ExogenousState<T>> exogenous_state_;
  std::unique_ptr<const EndogenousState<T>> endogenous_state_;
  double value_;

private:
};
}
#endif // _DP_RESULT_H_
