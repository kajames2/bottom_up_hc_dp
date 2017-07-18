#ifndef _ENDOGENOUS_ITERATOR_FACTORY_H_
#define _ENDOGENOUS_ITERATOR_FACTORY_H_

#include "endogenous_iterator.h"
#include "exogenous_state.h"

#include <memory>

namespace genericdp {
template <class T> class EndogenousIteratorFactory {
public:
  virtual std::unique_ptr<EndogenousIterator<T>> GetIterator(const ExogenousState<T>& input) const = 0;
};
} // namespace genericdp
#endif // _ENDOGENOUS_ITERATOR_FACTORY_H_
