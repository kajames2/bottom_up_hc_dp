#ifndef _EXOGENOUS_STATE_H_
#define _EXOGENOUS_STATE_H_

#include <memory>
#include <string>

namespace genericdp {
template <class T> class ExogenousState {
public:
  virtual T GetState() const = 0;
  virtual std::unique_ptr<ExogenousState<T>> Clone() const = 0;

  virtual std::string GetString() const = 0;
  virtual std::string GetHeader() const = 0;

  friend std::ostream &operator<<(std::ostream &out,
                                  const ExogenousState<T> &b) {
    out << b.GetString();
    return out;
  }
  
  ExogenousState() = default;
  ExogenousState(const ExogenousState &) = delete;
  ExogenousState &operator=(const ExogenousState &) = delete;
  virtual ~ExogenousState() {}
};
} // namespace genericdp
#endif // _EXOGENOUS_STATE_H_
