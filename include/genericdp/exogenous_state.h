#ifndef _EXOGENOUS_STATE_H_
#define _EXOGENOUS_STATE_H_

namespace genericdp {
template <class T> class ExogenousState {
public:
  virtual T GetState() const = 0;
  virtual ~ExogenousState() {}
};
} // namespace genericdp
#endif // _EXOGENOUS_STATE_H_
