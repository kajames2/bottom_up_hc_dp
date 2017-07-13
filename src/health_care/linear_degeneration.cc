#include "linear_degeneration.h"
#include <cmath>

namespace healthcare {

LinearDegeneration::LinearDegeneration(
    double degen_slope, double degen_intercept)
    : degen_slope_(degen_slope),
      degen_intercept_(degen_intercept) {}

int LinearDegeneration::GetDegeneration(int period) const {
  return std::round(degen_intercept_ + degen_slope_ * period);
}

} // namespace healthcare
