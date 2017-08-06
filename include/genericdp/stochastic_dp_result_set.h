#ifndef _STOCHASTIC_DP_RESULT_SET_H_
#define _STOCHASTIC_DP_RESULT_SET_H_

#include "dp_result_interface.h"
#include "endogenous_state.h"
#include "exogenous_state.h"
#include "stochastic_dp_result.h"

#include <iostream>
#include <string>
#include <vector>

namespace genericdp {
template <class T> class StochasticDPResultSet {
public:
  StochasticDPResultSet();
  StochasticDPResultSet(std::vector<StochasticDPResult<T>> result_vec);
  void AddResult(StochasticDPResult<T> result);
  double GetValue() const;

  StochasticDPResultSet(const StochasticDPResultSet &other)
      : result_vec_(other.result_vec_), value_(other.value_) {}
  StochasticDPResultSet &operator=(const StochasticDPResultSet &other) {
    using std::swap;
    StochasticDPResultSet copy(other);
    swap(*this, copy);
    return *this;
  }
    friend std::ostream &operator<<(std::ostream &out,
                                  const StochasticDPResultSet<T> &b) {
      out << b.result_vec_.at(0).GetHeader() << std::endl;
      for (const auto &result : b.result_vec_) {
        out << result.GetString() << std::endl;
      }
      out << "Expected Value: " << b.value_ << std::endl;
      return out;
  }

  StochasticDPResultSet(StochasticDPResultSet &&) = default;
  StochasticDPResultSet &operator=(StochasticDPResultSet &&) = default;

private:
  double CalculateValue() const;
  std::vector<StochasticDPResult<T>> result_vec_;
  double value_;
};

template <class T> StochasticDPResultSet<T>::StochasticDPResultSet() {}
template <class T>
StochasticDPResultSet<T>::StochasticDPResultSet(
    std::vector<StochasticDPResult<T>> result_vec)
    : result_vec_(std::move(result_vec)) {
  value_ = CalculateValue();
}

template <class T>
void StochasticDPResultSet<T>::AddResult(StochasticDPResult<T> result) {
  result_vec_.push_back(std::move(result));
  value_ = CalculateValue();
}

template <class T> double StochasticDPResultSet<T>::GetValue() const {
  return value_;
}

template <class T> double StochasticDPResultSet<T>::CalculateValue() const {
  double expected_value = 0;
  for (auto &result : result_vec_) {
    expected_value += result.GetValue() * result.GetProbability();
  }
  return expected_value;
}

} // namespace genericdp

#endif // _STOCHASTIC_DP_RESULT_SET_H_
