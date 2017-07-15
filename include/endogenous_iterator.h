#ifndef _ENDOGENOUS_ITERATOR_H_
#define _ENDOGENOUS_ITERATOR_H_

#include "endogenous_state.h"

#include <iterator>
namespace genericdp {
template <class T> class EndogenousIterator:
      public std::iterator<std::input_iterator_tag, EndogenousState<T>> {
public:
  using reference = EndogenousState<T> const&;
  using pointer = EndogenousState<T> const*;

  EndogenousIterator(): done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() const { return state_; }
  pointer operator->() const { return &state_; }

  virtual EndogenousIterator<T>& operator++() = 0;

protected:
  EndogenousIterator(EndogenousState<T> state) : state_(state), done_(false) {}
  bool done_;
  EndogenousState<T> state_;
};
}  // namespace genericdp
#endif  // _ENDOGENOUS_ITERATOR_H_
