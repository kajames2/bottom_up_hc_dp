#ifndef _SHIFTED_LOGISTIC_REGENERATION_H_
#define _SHIFTED_LOGISTIC_REGENERATION_H_

#include "regeneration.h"
#include <vector>

namespace healthcare {

class ShiftedLogisticRegeneration : public Regeneration {
public:
  ShiftedLogisticRegeneration(double k);
  int GetHealthRegained(int health_investment, int health) const override;

private:
  double k_;
};

} // namespace healthcare
#endif // _SHIFTED_LOGISTIC_REGENERATION_H_
