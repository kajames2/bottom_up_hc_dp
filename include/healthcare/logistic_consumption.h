#ifndef _LOGISTIC_CONSUMPTION_H_
#define _LOGISTIC_CONSUMPTION_H_

#include "consumption.h"

#include <vector>

namespace healthcare {

class LogisticConsumption : public Consumption {
public:
  LogisticConsumption(double k);
  double GetLifeEnjoyment(int health, int life_investment) const override;

private:
  double k_;
};

} // namespace healthcare
#endif // _LOGISTIC_CONSUMPTION_H_
