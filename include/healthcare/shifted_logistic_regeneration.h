#ifndef _SHIFTED_LOGISTIC_REGENERATION_H_
#define _SHIFTED_LOGISTIC_REGENERATION_H_

#include "regeneration.h"
#include <array>
#include <vector>

namespace healthcare {

class ShiftedLogisticRegeneration : public Regeneration {
public:
  ShiftedLogisticRegeneration(double k);
  ShiftedLogisticRegeneration(double k, int max_investment);
  int GetHealthRegained(int health, int health_investment) const override;

private:
  int CalculateHealthRegained(int health, int health_investment) const;
  std::vector<std::array<int, 101>> cache_;
  double k_;
};

} // namespace healthcare
#endif // _SHIFTED_LOGISTIC_REGENERATION_H_
