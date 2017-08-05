#ifndef _STOCHASTIC_DP_H_
#define _STOCHASTIC_DP_H_

#include "dp_storage.h"
#include "dp_template.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "state_iterator.h"
#include "stochastic_dp_result.h"
#include "stochastic_dp_result_set.h"
#include "stochastic_exogenous_set_factory.h"
#include "stochastic_exogenous_state.h"
#include "value_strategy.h"

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

namespace genericdp {
template <class T>
class StochasticDP : public DPTemplate<T, StochasticDPResult> {
public:
  StochasticDP(std::unique_ptr<DPStorage<T, StochasticDPResult>> storage,
               std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
               std::unique_ptr<const ValueStrategy<T>> calculator,
               std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact);
  StochasticDPResultSet<T> GetSolution(const T &init_state);
  void Train(const T &state) override;

private:
  std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact_;
};

template <class T>
StochasticDP<T>::StochasticDP(
    std::unique_ptr<DPStorage<T, StochasticDPResult>> storage,
    std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
    std::unique_ptr<const ValueStrategy<T>> calculator,
    std::unique_ptr<const StochasticExogenousSetFactory<T>> ex_fact)
    : DPTemplate<T, StochasticDPResult>(std::move(storage), std::move(fact),
                                        std::move(calculator)),
      ex_fact_(std::move(ex_fact)) {}

template <class T>
StochasticDPResultSet<T> StochasticDP<T>::GetSolution(const T &state) {
  StochasticDPResultSet<T> result;
  try {
    result = this->GetOptimalResult(state);
  } catch (const std::out_of_range &oor) {
    std::cerr << "A state was out of range for storage." << std::endl
              << oor.what() << std::endl;
  }
  return result;
}

template <class T> void StochasticDP<T>::Train(const T &state) {
  auto ex_state_set = ex_fact_->GetExogenousSet(state);
  StochasticDPResultSet<T> opt_result_set;
  for (auto &ex_state : ex_state_set) {
    auto opt_state_value = this->CalculateOptimal(*ex_state.GetExogenous());
    StochasticDPResult<T> opt_result(ex_state.GetExogenous()->Clone(), std::move(opt_state_value.first), opt_state_value.second, ex_state.GetProbability());
    opt_result_set.push_back(std::move(opt_result));
  }
  this->storage_->StoreOptimalValue(state, opt_result_set.GetValue());
  this->storage_->StoreOptimalResult(state, opt_result_set);
}

} // namespace genericdp
#endif // _STOCHASTIC_DP_H_
