#ifndef _PERIOD_RESULT_H_
#define _PERIOD_RESULT_H_

#include "health_state.h"
#include "investment.h"

namespace healthcare {
struct PeriodResult {
  PeriodResult() {}
  PeriodResult(HealthState end_s, Investment i, double le,
               HealthState inv_s = HealthState(0, 0, 0, 0))
      : state(end_s), investment(i), enjoyment(le){}

  HealthState state;
  Investment investment;
  double enjoyment;

  bool operator==(const PeriodResult &other) const {
    return state == other.state &&
           investment == other.investment && enjoyment == other.enjoyment;
  }
};

} // namespace healthcare
#endif // _PERIOD_RESULT_H_
