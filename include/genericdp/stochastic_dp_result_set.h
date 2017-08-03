#ifndef _STOCHASTIC_DP_RESULT_SET_H_
#define _STOCHASTIC_DP_RESULT_SET_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include "stochastic_dp_result.h"

#include <vector>

namespace genericdp {
template <class T> class StochasticDPResultSet {
public:
  StochasticDPResultSet();
  StochasticDPResultSet(std::vector<StochasticDPResult<T>> result_vec);
  void AddResult(StochasticDPResult<T> result);
  double GetValue() const;

private:
  double CalculateValue() const;
  double value;
  std::vector<StochasticDPResult<T>> result_vec_;
};

template <class T> StochasticDPResultSet<T>::StochasticDPResultSet() {}
template <class T>
StochasticDPResultSet<T>::StochasticDPResultSet(
    std::vector<StochasticDPResult<T>> result_vec)
    : result_vec_(std::move(result_vec)) {
  value = CalculateValue();
}

template <class T>
void StochasticDPResultSet<T>::AddResult(StochasticDPResult<T> result) {
  result_vec_.push_back(std::move(result));
  value = CalculateValue();
}

template <class T> double StochasticDPResultSet<T>::GetValue() const {
  return value
}

template <class T> double StochasticDPResultSet<T>::CalculateValue() const {
  double expected_value = 0;
  for (auto &result : result_vec_) {
    expected_value += result.value * result.probability;
  }
  return expected_value;
}
} // namespace genericdp

#endif // _STOCHASTIC_DP_RESULT_SET_H_
