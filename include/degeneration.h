#ifndef _DEGENERATION_H_
#define _DEGENERATION_H_

namespace healthcare {

class Degeneration {
public:
  virtual int GetDegeneration(int period) const = 0;
};

} // namespace healthcare
#endif // _DEGENERATION_H_
