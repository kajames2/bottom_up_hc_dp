#ifndef _DP_RESULT_H_
#define _DP_RESULT_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include "dp_result_interface.h"

#include <memory>

namespace genericdp {
template <class T> class DPResult : public DPResultInterface<T> {
public:
  DPResult(std::unique_ptr<const ExogenousState<T>> ex,
           std::unique_ptr<const EndogenousState<T>> end, double val)
      : exogenous_state_(std::move(ex))
      , endogenous_state_(std::move(end)) { value_ = val;}
  DPResult()
      : exogenous_state_(nullptr)
      , endogenous_state_(nullptr) { value_ = -1;}

  std::unique_ptr<DPResultInterface<T>> Clone() const override {
    return std::make_unique<DPResult>(exogenous_state_->Clone(), endogenous_state_->Clone(), GetValue());
  };

  std::string GetString() const override {
    return exogenous_state_->GetString() + ", "
        + endogenous_state_->GetString() + ", "
        + std::to_string(GetValue());
  }

  std::string GetHeader() const override {
    return exogenous_state_->GetHeader() + ", "
        + endogenous_state_->GetHeader() + ", "
        + "Value";
  }

  T GetState() const override {
    return endogenous_state_->GetState();
  }

  double GetValue() const override {
    return value_;
  }

 protected:
  std::unique_ptr<const ExogenousState<T>> exogenous_state_;
  std::unique_ptr<const EndogenousState<T>> endogenous_state_;
  double value_;
};
}

#endif // _DETERMINISTIC_DP_RESULT_H_