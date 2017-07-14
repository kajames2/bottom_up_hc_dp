#ifndef _ENDOGENOUS_ITERATOR_FACTORY_H_
#define _ENDOGENOUS_ITERATOR_FACTORY_H_

#include "endogenous_iterator.h"

#include <memory>

namespace genericdp {
template <class Intermediate, class End> class EndogenousIteratorFactory {
public:
  EndogenousIterator<End> GetIterator(Intermediate input);
};
} // namespace genericdp
#endif // _ENDOGENOUS_ITERATOR_FACTORY_H_
