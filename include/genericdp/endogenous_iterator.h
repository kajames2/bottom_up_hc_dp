#ifndef _ENDOGENOUS_ITERATOR_H_
#define _ENDOGENOUS_ITERATOR_H_

#include "endogenous_state.h"
#include "exogenous_state.h"
#include <iterator>
#include <memory>

namespace genericdp {
template <class T>
class EndogenousIterator
    : public std::iterator<std::input_iterator_tag, EndogenousState<T>> {
public:
  using reference = const EndogenousState<T> &;
  using pointer = const EndogenousState<T> *;

  EndogenousIterator() : done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() const { return *state_; }
  pointer operator->() const { return state_; }

  virtual EndogenousIterator<T> &operator++() = 0;

  EndogenousIterator(const EndogenousIterator&) = delete;
  EndogenousIterator& operator=(const EndogenousIterator&) = delete;
  virtual ~EndogenousIterator() {}
protected:
  EndogenousIterator(const ExogenousState<T> &state) : state_(), done_(false) {}
  bool done_;
  EndogenousState<T>* state_;
};
} // namespace genericdp
#endif // _ENDOGENOUS_ITERATOR_H_
