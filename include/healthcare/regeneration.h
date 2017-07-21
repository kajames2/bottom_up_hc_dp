#ifndef _REGENERATION_H_
#define _REGENERATION_H_

namespace healthcare {

class Regeneration {
 public:
  virtual int GetHealthRegained(int health_investment, int health) const = 0;
  virtual ~Regeneration() {}
  Regeneration(const Regeneration&) = delete;
  Regeneration& operator=(const Regeneration&) = delete;
};

}  // namespace healthcare
#endif  // _REGENERATION_H_
