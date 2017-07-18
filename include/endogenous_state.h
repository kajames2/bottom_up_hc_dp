#ifndef _ENDOGENOUS_STATE_H_
#define _ENDOGENOUS_STATE_H_

#include <memory>
#include <string>

namespace genericdp {
template <class T> class EndogenousState {
public:
  virtual T GetState() const = 0;
  virtual double GetValue() const = 0;
  virtual std::unique_ptr<EndogenousState<T>> Clone() const = 0;
  virtual ~EndogenousState() {}

  friend std::ostream &operator<<(std::ostream &out,
                                  const EndogenousState<T> &b) {
    b.Print(out);
    return out;
  }

private:
  virtual void Print(std::ostream &) const = 0;
};
} // namespace genericdp
#endif // _ENDOGENOUS_STATE_H_
