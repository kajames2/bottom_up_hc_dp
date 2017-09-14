#ifndef _FRACTIONAL_CONSUMPTION_H_
#define _FRACTIONAL_CONSUMPTION_H_

#include "cached_consumption.h"

#include <array>
#include <vector>
#include <memory>

namespace healthcare {

class FractionalConsumption : public CachedConsumption {
public:
  FractionalConsumption(double j);
  FractionalConsumption(double j, int max_investment);

private:
  double CalculateLifeEnjoyment(int health, int life_investment) const override;
  double j_;
};

} // namespace healthcare
#endif // _FRACTIONAL_CONSUMPTION_H_
