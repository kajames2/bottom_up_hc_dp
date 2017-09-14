#ifndef _SHIFTED_LOGISTIC_REGENERATION_H_
#define _SHIFTED_LOGISTIC_REGENERATION_H_

#include "cached_regeneration.h"
#include <array>
#include <vector>

namespace healthcare {

class ShiftedLogisticRegeneration : public CachedRegeneration {
public:
  ShiftedLogisticRegeneration(double k);
  ShiftedLogisticRegeneration(double k, int max_investment);

private:
  int CalculateHealthRegained(int health, int health_investment) const override;
  double k_;

};

} // namespace healthcare
#endif // _SHIFTED_LOGISTIC_REGENERATION_H_
