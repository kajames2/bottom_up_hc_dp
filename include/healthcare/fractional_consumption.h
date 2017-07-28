#ifndef _FRACTIONAL_CONSUMPTION_H_
#define _FRACTIONAL_CONSUMPTION_H_

#include "consumption.h"

#include <array>
#include <vector>

namespace healthcare {

class FractionalConsumption : public Consumption {
public:
  FractionalConsumption(double j);
  double GetLifeEnjoyment(int life_investment, int health) const override;

private:
  double CalculateEnjoyment(int life_investment, int health) const;
  double j_;
  std::vector<std::array<float, 101>> cache_;
};

} // namespace healthcare
#endif // _FRACTIONAL_CONSUMPTION_H_
