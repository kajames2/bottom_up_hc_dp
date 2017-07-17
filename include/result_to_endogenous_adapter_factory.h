#ifndef _RESULT_TO_ENDOGENOUS_ADAPTER_FACTORY_H_
#define _RESULT_TO_ENDOGENOUS_ADAPTER_FACTORY_H_

#include "period_result.h"
#include "period_result_factory.h"
#include "result_to_endogenous_adapter.h"

#include <memory>
namespace healthcaredp {
class ResultToEndogenousAdapterFactory {
public:
  ResultToEndogenousAdapterFactory(healthcare::PeriodResultFactory result_fact);
  ResultToEndogenousAdapter
  GetEndogenousResult(const healthcare::HealthState &state,
                      const healthcare::Investment &investment) const;
  int GetHealthRegained(const healthcare::HealthState &state,
                        const healthcare::Investment &investment) const;

private:
  healthcare::PeriodResultFactory result_fact_;
};
} // namespace healthcaredp
#endif // _RESULT_TO_ENDOGENOUS_ADAPTER_FACTORY_H_