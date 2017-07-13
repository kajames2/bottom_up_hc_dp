#ifndef _DP_STATE_ITERATOR_H_
#define _DP_STATE_ITERATOR_H_

#include <iterator>

namespace genericdp {
template <class T> class DPStateIterator:
  public std::iterator<std::input_iterator_tag, T> {
public:
  using reference = T const&;
  using pointer = T const*;

  DPStateIterator(): done_(false) {}

  explicit operator bool() const { return !done_; }
  reference operator*() const { return state_; }
  pointer operator->() const { return &state_; }

  virtual DPStateIterator<T>& operator++() = 0;

  /*  DPStateIterator<T> operator++(int) {
    DPStateIterator<T> const tmp(*this);
    ++*this;
    return tmp;
    }*/

protected:
  DPStateIterator(const T& state) : state_(state), done_(false) {}
  bool done_;
  T state_;
};
}  // namespace genericdp
#endif  // _DP_STATE_ITERATOR_H_
