#ifndef _DP_H_
#define _DP_H_

#include "dp_result.h"
#include "dp_storage.h"
#include "dp_template.h"
#include "endogenous_iterator_factory.h"
#include "endogenous_state.h"
#include "exogenous_factory.h"
#include "state_iterator.h"
#include "value_strategy.h"

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

namespace genericdp {
template <class T> class DP : public DPTemplate<T, DPResult<T>> {
public:
  DP(std::unique_ptr<DPStorage<T, DPResult<T>>> storage,
     std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
     std::unique_ptr<const ValueStrategy<T>> calculator,
     std::unique_ptr<const ExogenousFactory<T>> ex_fact);

  std::vector<DPResult<T>> GetSolution(const T &init_state);
  void Train(const T &state) override;

private:
  std::unique_ptr<const ExogenousFactory<T>> ex_fact_;
};

template <class T>
DP<T>::DP(std::unique_ptr<DPStorage<T, DPResult<T>>> storage,
          std::unique_ptr<const EndogenousIteratorFactory<T>> fact,
          std::unique_ptr<const ValueStrategy<T>> calculator,
          std::unique_ptr<const ExogenousFactory<T>> ex_fact)
    : DPTemplate<T, DPResult<T>>(std::move(storage), std::move(fact), std::move(calculator))
    , ex_fact_(std::move(ex_fact)) {}

template <class T>
std::vector<DPResult<T>> DP<T>::GetSolution(const T &init_state) {
  std::vector<DPResult<T>> solution;
  T cur_state = init_state;
  try {
    while (!this->storage_->IsTerminalState(cur_state)) {
      auto result = this->GetOptimalResult(cur_state);
      solution.push_back(result);
      cur_state = result.GetState();
    }
  } catch (const std::out_of_range &oor) {
    std::cerr << "A state was out of range for storage." << std::endl
              << oor.what() << std::endl;
  }
  return solution;
}

template <class T> void DP<T>::Train(const T &state) {
  auto ex_state = ex_fact_->GetExogenous(state);
  auto opt_state_value = this->CalculateOptimal(*ex_state);
  DPResult<T> opt_result(ex_state->Clone(), std::move(opt_state_value.first),
                         opt_state_value.second);
  this->storage_->StoreOptimalResult(state, opt_result, opt_state_value.second);
}
} // namespace genericdp
#endif // _DP_H_
