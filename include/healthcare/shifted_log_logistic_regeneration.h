#ifndef _SHIFTED_LOG_LOGISTIC_REGENERATION_H_
#define _SHIFTED_LOG_LOGISTIC_REGENERATION_H_

#include "cached_regeneration.h"
#include <array>
#include <vector>

namespace healthcare {

class ShiftedLogLogisticRegeneration : public CachedRegeneration {
public:
  ShiftedLogLogisticRegeneration(double alpha, double beta);
  ShiftedLogLogisticRegeneration(double alpha, double beta, int max_investment);

private:
  int CalculateHealthRegained(int health, int health_investment) const override;
  double alpha_, beta_;
};

} // namespace healthcare
#endif // _SHIFTED_LOG_LOGISTIC_REGENERATION_H_
