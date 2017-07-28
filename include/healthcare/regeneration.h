#ifndef _REGENERATION_H_
#define _REGENERATION_H_

namespace healthcare {

class Regeneration {
 public:
  Regeneration() = default;
  Regeneration(const Regeneration&) = delete;
  Regeneration& operator=(const Regeneration&) = delete;
  virtual ~Regeneration() {}

  virtual int GetHealthRegained(int health_investment, int health) const = 0;
 private:
};

}  // namespace healthcare
#endif  // _REGENERATION_H_
