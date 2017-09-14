#include "log_logistic_consumption.h"

#include <cmath>
#include <vector>

namespace healthcare {

LogLogisticConsumption::LogLogisticConsumption(double alpha, double beta,
                                               double c)
    : LogLogisticConsumption(alpha, beta, c, 300) {}
LogLogisticConsumption::LogLogisticConsumption(double alpha, double beta,
                                               double c, int max_investment)
    : alpha_(alpha), beta_(beta), c_(c), CachedConsumption(max_investment) {
  FillCache();
}

double
LogLogisticConsumption::CalculateLifeEnjoyment(int health,
                                               int life_investment) const {
  return c_ * health / (1 + std::pow((life_investment) / alpha_, -beta_));
}

} // namespace healthcare
