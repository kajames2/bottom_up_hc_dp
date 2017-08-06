#ifndef _STOCHASTIC_DP_RESULT_H_
#define _STOCHASTIC_DP_RESULT_H_

#include "dp_result.h"
#include "endogenous_state.h"
#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class StochasticDPResult : public DPResult<T> {
public:
  StochasticDPResult(std::unique_ptr<const ExogenousState<T>> ex,
                     std::unique_ptr<const EndogenousState<T>> end, double val,
                     double probability)
      : DPResult<T>(std::move(ex), std::move(end), val),
        probability_(probability) {}
  StochasticDPResult() : DPResult<T>(), probability_(0) {}

  StochasticDPResult(const StochasticDPResult &other)
      : DPResult<T>(other), probability_(other.probability_) {}
  StochasticDPResult &operator=(const StochasticDPResult &other) {
    using std::swap;
    StochasticDPResult copy(other);
    swap(*this, copy);
    return *this;
  }
  StochasticDPResult(StochasticDPResult &&) = default;
  StochasticDPResult &operator=(StochasticDPResult &&) = default;

  std::string GetString() const override {
    return std::to_string(probability_) + ", " + DPResult<T>::GetString();
  }

  std::string GetHeader() const override {
    return std::string("Probability") + ", " + DPResult<T>::GetHeader();
  }
  double GetProbability() const { return probability_; }

private:
  double probability_;
};
}
#endif // _STOCHASTIC_DP_RESULT_H_
