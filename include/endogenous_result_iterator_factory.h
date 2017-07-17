#ifndef _ENDOGENOUS_RESULT_ITERATOR_FACTORY_H_
#define _ENDOGENOUS_RESULT_ITERATOR_FACTORY_H_

#include "consumption.h"
#include "endogenous_result_iterator.h"
#include "health_state.h"
#include "health_state_to_exogenous_adapter.h"
#include "regeneration.h"
#include "result_to_endogenous_adapter_factory.h"

#include <memory>

namespace healthcaredp {
class EndogenousResultIteratorFactory {
public:
  EndogenousResultIteratorFactory(
      std::shared_ptr<const healthcare::Regeneration> regen,
      std::shared_ptr<const healthcare::Consumption> consumption,
      int max_cash_on_hand = 0);
  EndogenousResultIteratorFactory(
      const ResultToEndogenousAdapterFactory &state_factory,
      int max_remaining_cash = 0);
  EndogenousResultIterator GetEndogenousIterator(
      const genericdp::ExogenousState<healthcare::HealthState> &state) const;

private:
  ResultToEndogenousAdapterFactory state_factory_;
  int max_remaining_cash_;
};
} // namespace healthcaredp
#endif // _ENDOGENOUS_RESULT_ITERATOR_FACTORY_H_
