#ifndef _SHIFTED_LOGISTIC_REGENERATION_H_
#define _SHIFTED_LOGISTIC_REGENERATION_H_

#include "regeneration.h"
#include <array>

namespace healthcare {

class ShiftedLogisticRegeneration : public Regeneration {
public:
  ShiftedLogisticRegeneration(double k);
  int GetHealthRegained(int health_investment, int health) const override;

private:
  int CalculateHealthRegained(int health_investment, int health) const;
  std::array<std::array<int, 101>, 301> cache_;
  double k_;
};

} // namespace healthcare
#endif // _SHIFTED_LOGISTIC_REGENERATION_H_
