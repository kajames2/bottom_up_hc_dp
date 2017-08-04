#ifndef _STOCHASTIC_DP_RESULT_H_
#define _STOCHASTIC_DP_RESULT_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include "dp_result.h"

#include <memory>

namespace genericdp {
template <class T> class StochasticDPResult : public DPResult<T> {
public:
  StochasticDPResult(std::unique_ptr<const ExogenousState<T>> ex,
                     std::unique_ptr<const EndogenousState<T>> end, double val, double probability)
      : DPResult<T>(std::move(ex), std::move(end), val)
      , probability_(probability) {}
  StochasticDPResult() : DPResult<T>(), probability_(0) {}

  virtual std::unique_ptr<DPResultInterface<T>> Clone() const override {
    std::make_unique<StochasticDPResult>(exogenous_state_->Clone(), endogenous_state_->Clone(), GetValue());
  };

  virtual std::string GetString() const override {
    return std::to_string(probability_) + ", "
        + DPResult<T>::GetString();
  }
  
  virtual std::string GetHeader() const override {
    return std::string("Probability") + ", "
        + DPResult<T>::GetHeader();
  }

private:
  double probability_;
};
}
#endif // _STOCHASTIC_DP_RESULT_H_
