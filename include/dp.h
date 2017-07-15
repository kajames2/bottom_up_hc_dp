#ifndef _DP_H_
#define _DP_H_

#include "decision_optimizer.h"
#include "dp_storage.h"
#include "endogenous_state.h"
#include "exogenous_strategy.h"
#include "state_iterator.h"

#include <memory>
#include <vector>
namespace genericdp {
template <class T> class DP {
public:
  DP(std::unique_ptr<DPStorage<T>> storage,
     std::shared_ptr<const ExogenousStrategy<T>> exo_strat,
     std::shared_ptr<const DecisionOptimizer<T>> decision_maker);
  void Train(StateIterator<T> it);
  std::vector<EndogenousState<T>> GetSolution(T init_state) const;

private:
  std::unique_ptr<DPStorage<T>> storage_;
  std::shared_ptr<const ExogenousStrategy<T>> exo_strat_;
  std::shared_ptr<const DecisionOptimizer<T>> decision_maker_;
};

template <class T>
DP<T>::DP(std::unique_ptr<DPStorage<T>> storage,
       std::shared_ptr<const ExogenousStrategy<T>> exo_strat,
       std::shared_ptr<const DecisionOptimizer<T>> decision_maker)
    : storage_(storage), exo_strat_(exo_strat_),
      decision_maker_(decision_maker) {}

template <class T>
void DP<T>::Train(StateIterator<T> state_it) {
  for(auto it = state_it; it; ++it) {
    ExogenousState<T> ex_state = exo_strat_->GetExogenous(*it);
    std::pair<EndogenousState<T>, double> opt_state_value = decision_maker_->FindOptimal(ex_state, storage_);
    storage_->StoreEndogenous(*it, opt_state_value.first);
    storage_->StoreValue(*it, opt_state_value.second);
  }
}

template<class T>
std::vector<EndogenousState<T>> DP<T>::GetSolution(T init_state) const {
  auto solution = std::vector<EndogenousState<T>>();
  T cur_state = init_state;
  while(!storage_->IsTerminalState(cur_state)) {
    cur_state = storage_->GetEndogenous(cur_state).state;
    solution.push_back(cur_state);
  }
  return solution;
}

} // namespace genericdp
#endif // _DP_H_
