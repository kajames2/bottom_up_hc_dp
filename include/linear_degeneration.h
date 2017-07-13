#ifndef _LINEAR_DEGENERATION_H_
#define _LINEAR_DEGENERATION_H_

#include "degeneration.h"

namespace healthcare {
class LinearDegeneration : public Degeneration {
public:
  LinearDegeneration(double degen_slope, double degen_intercept);
  int GetDegeneration(int period) const override;

private:
  double degen_slope_;
  double degen_intercept_;
};

} // namespace healthcare
#endif // _LINEAR_DEGENERATION_H_
