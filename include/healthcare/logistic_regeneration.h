#ifndef _LOGISTIC_REGENERATION_H_
#define _LOGISTIC_REGENERATION_H_

#include "regeneration.h"
#include <vector>

namespace healthcare {

class LogisticRegeneration : public Regeneration {
public:
  LogisticRegeneration(double gamma, double sigma, double r);
  int GetHealthRegained(int health_investment, int health) const override;

private:
  double gamma_;
  double sigma_;
  double r_;
};

} // namespace healthcare
#endif // _LOGISTIC_REGENERATION_H_
