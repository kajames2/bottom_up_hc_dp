#ifndef _PERIOD_RESULT_FACTORY_H_
#define _PERIOD_RESULT_FACTORY_H_

#include "consumption.h"
#include "health_state.h"
#include "investment.h"
#include "period_result.h"
#include "regeneration.h"
#include <memory>

namespace healthcare {
class PeriodResultFactory {
public:
  PeriodResultFactory(std::shared_ptr<const Regeneration> regeneration,
                      std::shared_ptr<const Consumption> consumption);
  PeriodResult GetPeriodResult(const HealthState &state,
                               const Investment &investment) const;
  HealthState GetPostInvestmentState(const HealthState &state,
                                     const Investment &investment) const;
  double GetLifeEnjoyment(const HealthState &state,
                          const Investment &investment) const;
  double CalculateLifeEnjoyment(int end_health, int life_investment) const;
  int GetHealthRegained(const HealthState &state,
                        const Investment &investment) const;

private:
  int GetHealthAtEnd(const HealthState &state,
                     const Investment &investment) const;
  int GetCashAtEnd(const HealthState &state,
                   const Investment &investment) const;

  std::shared_ptr<const Regeneration> regeneration_;
  std::shared_ptr<const Consumption> consumption_;
};
} // namespace healthcare
#endif // _PERIOD_RESULT_FACTORY_H_
