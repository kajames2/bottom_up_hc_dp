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

  virtual std::string GetString() const = 0;
  virtual std::string GetHeader() const = 0;

  friend std::ostream &operator<<(std::ostream &out,
                                  const EndogenousState<T> &b) {
    out << b.GetString();
    return out;
  }
  EndogenousState() = default;
  EndogenousState(const EndogenousState&) = delete;
  EndogenousState& operator=(const EndogenousState&) = delete;
  virtual ~EndogenousState() {}
 private:

};
} // namespace genericdp
#endif // _ENDOGENOUS_STATE_H_
