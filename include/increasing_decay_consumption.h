#ifndef _INCREASING_DECAY_CONSUMPTION_H_
#define _INCREASING_DECAY_CONSUMPTION_H_

#include "consumption.h"

#include <vector>

namespace healthcare {

class IncreasingDecayConsumption : public Consumption {
public:
  IncreasingDecayConsumption(double alpha, double c, double beta);
  double GetLifeEnjoyment(int life_investment, int health) const override;

private:
  double alpha_;
  double c_;
  double beta_;
};

} // namespace healthcare
#endif // _INCREASING_DECAY_CONSUMPTION_H_
