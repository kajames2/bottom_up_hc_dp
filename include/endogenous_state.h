#ifndef _ENDOGENOUS_STATE_H_
#define _ENDOGENOUS_STATE_H_

#include <memory>

namespace genericdp {
template <class T> class EndogenousState {
public:
  virtual T GetState() const = 0;
  virtual double GetValue() const = 0;
  virtual std::shared_ptr<EndogenousState<T>> Clone() const;
};
} // namespace genericdp
#endif // _ENDOGENOUS_STATE_H_
