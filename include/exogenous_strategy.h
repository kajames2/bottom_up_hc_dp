#ifndef _EXOGENOUS_STRATEGY_H_
#define _EXOGENOUS_STRATEGY_H_

#include <memory>

namespace genericdp {
template <class Start, class Intermediate> class ExogenousStrategy {
public:
  Intermediate AdvanceTime(Start state);
};
} // namespace genericdp
#endif // _EXOGENOUS_STRATEGY_H_
