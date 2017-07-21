#ifndef _DEGENERATION_H_
#define _DEGENERATION_H_

namespace healthcare {

class Degeneration {
public:
  virtual int GetDegeneration(int period) const = 0;
  Degeneration() = default;
  Degeneration(const Degeneration&) = delete;
  Degeneration& operator=(const Degeneration&) = delete;
  virtual ~Degeneration() {}
};

} // namespace healthcare
#endif // _DEGENERATION_H_
