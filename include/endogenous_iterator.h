#ifndef _ENDOGENOUS_ITERATOR_H_
#define _ENDOGENOUS_ITERATOR_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include <iterator>
#include <memory>

namespace genericdp {
template <class T> class EndogenousIterator:
      public std::iterator<std::input_iterator_tag, EndogenousState<T>> {
public:
  using Endog = EndogenousState<T>;
  using Exog = ExogenousState<T>;
  using reference = Endog const&;
  using pointer = Endog const*;
  
  EndogenousIterator(): done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() const { return *state_; }
  pointer operator->() const { return &(*state_); }

  virtual EndogenousIterator<T>& operator++() = 0;
  virtual ~EndogenousIterator() {}
protected:
  EndogenousIterator(const Exog& state) : state_(), done_(false) {}
  bool done_;
  std::shared_ptr<Endog> state_;
};
}  // namespace genericdp
#endif  // _ENDOGENOUS_ITERATOR_H_
