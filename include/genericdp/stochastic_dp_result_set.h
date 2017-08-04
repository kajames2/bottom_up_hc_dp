#ifndef _STOCHASTIC_DP_RESULT_SET_H_
#define _STOCHASTIC_DP_RESULT_SET_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include "dp_result_interface.h"
#include "stochastic_dp_result.h"

#include <vector>
#include <string>
#include <iostream>

namespace genericdp {
template <class T> class StochasticDPResultSet : public DPResultInterface<T> {
public:
  StochasticDPResultSet();
  StochasticDPResultSet(std::vector<StochasticDPResult<T>> result_vec);
  void AddResult(StochasticDPResult<T> result);
  T GetState() const override;
  double GetValue() const override;
  std::string GetHeader() const override;
  std::string GetString() const override;
private:
  double CalculateValue() const;
  std::vector<StochasticDPResult<T>> result_vec_;
  double value;
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
  return value;
}

template <class T> double StochasticDPResultSet<T>::CalculateValue() const {
  double expected_value = 0;
  for (auto &result : result_vec_) {
    expected_value += result.value * result.probability;
  }
  return expected_value;
}

template <class T> std::string StochasticDPResultSet<T>::GetString() const {
  std::string out_str = "";
  for (const auto& result : result_vec_) {
    out_str += result.GetString() + std::endl;
  }
  return out_str;
}

template <class T> std::string StochasticDPResultSet<T>::GetHeader() const {
    return result_vec_.at(0).GetHeader();
}

template <class T> T StochasticDPResultSet<T>::GetState() const {
  return result_vec_.at(0).GetState();
}

} // namespace genericdp

#endif // _STOCHASTIC_DP_RESULT_SET_H_
