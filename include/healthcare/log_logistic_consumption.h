#ifndef _LOG_LOGISTIC_CONSUMPTION_H_
#define _LOG_LOGISTIC_CONSUMPTION_H_

#include "cached_consumption.h"
#include <array>
#include <vector>

namespace healthcare {

class LogLogisticConsumption : public CachedConsumption {
public:
  LogLogisticConsumption(double alpha, double beta, double c);
  LogLogisticConsumption(double alpha, double beta, double c,
                         int max_investment);

private:
  double CalculateLifeEnjoyment(int health, int life_investment) const override;
  double alpha_, beta_, c_;
};

} // namespace healthcare
#endif // _LOG_LOGISTIC_CONSUMPTION_H_
