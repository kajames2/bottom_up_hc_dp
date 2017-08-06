#ifndef _DP_RESULT_H_
#define _DP_RESULT_H_

#include "dp_result_interface.h"
#include "endogenous_state.h"
#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class DPResult {
public:
  DPResult(std::unique_ptr<const ExogenousState<T>> ex,
           std::unique_ptr<const EndogenousState<T>> end, double val);

  DPResult();
  DPResult(const DPResult &other);
  DPResult &operator=(const DPResult &other);
  DPResult(DPResult &&) = default;
  DPResult &operator=(DPResult &&) = default;

  std::string GetString() const;
  std::string GetHeader() const;

  T GetState() const;

  double GetValue() const;

private:
  std::unique_ptr<const ExogenousState<T>> exogenous_state_;
  std::unique_ptr<const EndogenousState<T>> endogenous_state_;
  double value_;
};

template <class T>
DPResult<T>::DPResult(std::unique_ptr<const ExogenousState<T>> ex,
                      std::unique_ptr<const EndogenousState<T>> end, double val)
    : exogenous_state_(std::move(ex)), endogenous_state_(std::move(end)),
      value_(val) {}

template <class T>
DPResult<T>::DPResult()
    : exogenous_state_(nullptr), endogenous_state_(nullptr), value_(-1) {}

template <class T>
DPResult<T>::DPResult(const DPResult &other)
    : exogenous_state_(other.exogenous_state_->Clone()),
      endogenous_state_(other.endogenous_state_->Clone()),
      value_(other.value_) {}

template <class T> DPResult<T> &DPResult<T>::operator=(const DPResult &other) {
  using std::swap;
  DPResult copy(other);
  swap(*this, copy);
  return *this;
}

template <class T> std::string DPResult<T>::GetString() const {
  return exogenous_state_->GetString() + ", " + endogenous_state_->GetString() +
         ", " + std::to_string(GetValue());
}

template <class T> std::string DPResult<T>::GetHeader() const {
  return exogenous_state_->GetHeader() + ", " + endogenous_state_->GetHeader() +
         ", " + "Value";
}

template <class T> T DPResult<T>::GetState() const {
  return endogenous_state_->GetState();
}

template <class T> double DPResult<T>::GetValue() const { return value_; }
}
#endif // _DP_RESULT_H_
