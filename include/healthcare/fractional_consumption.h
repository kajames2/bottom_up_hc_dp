#ifndef _FRACTIONAL_CONSUMPTION_H_
#define _FRACTIONAL_CONSUMPTION_H_

#include "consumption.h"

#include <array>
#include <vector>

namespace healthcare {

class FractionalConsumption : public Consumption {
public:
  FractionalConsumption(double j);
  FractionalConsumption(double j, int max_investment);
  double GetLifeEnjoyment(int health, int life_investment) const override;

private:
  double CalculateEnjoyment(int health, int life_investment) const;
  double j_;
  std::vector<std::array<float, 101>> cache_;
};

} // namespace healthcare
#endif // _FRACTIONAL_CONSUMPTION_H_
