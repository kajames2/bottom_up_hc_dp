#ifndef _FRACTIONAL_CONSUMPTION_H_
#define _FRACTIONAL_CONSUMPTION_H_

#include "consumption.h"

#include <vector>

namespace healthcare {

class FractionalConsumption : public Consumption {
public:
  FractionalConsumption(double j);
  double GetLifeEnjoyment(int life_investment, int health) const override;

private:
  double j_;
};

} // namespace healthcare
#endif // _FRACTIONAL_CONSUMPTION_H_
