#ifndef _DEGENERATION_H_
#define _DEGENERATION_H_

namespace healthcare {

class Degeneration {
public:
  virtual int GetDegeneration(int period) const = 0;
  virtual ~Degeneration() {}
  Degeneration(const Degeneration&) = delete;
  Degeneration& operator=(const Degeneration&) = delete;
};

} // namespace healthcare
#endif // _DEGENERATION_H_
