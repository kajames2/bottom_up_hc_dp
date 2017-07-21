#ifndef _STATE_ITERATOR_H_
#define _STATE_ITERATOR_H_

#include <iterator>

namespace genericdp {
template <class T>
class StateIterator : public std::iterator<std::input_iterator_tag, T> {
public:
  using reference = const T &;
  using pointer = const T *;

  StateIterator() : done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() const { return state_; }
  pointer operator->() const { return &state_; }

  virtual StateIterator<T> &operator++() = 0;
  virtual ~StateIterator() {}
  StateIterator(const StateIterator&) = delete;
  StateIterator& operator=(const StateIterator&) = delete;
protected:
  StateIterator(T state) : state_(state), done_(false) {}
  bool done_;
  T state_;
};
} // namespace genericdp
#endif // _STATE_ITERATOR_H_
