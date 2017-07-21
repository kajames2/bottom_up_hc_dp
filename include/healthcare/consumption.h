#ifndef _CONSUMPTION_H_
#define _CONSUMPTION_H_

namespace healthcare {

class Consumption {
 public:
  virtual double GetLifeEnjoyment(int life_investment, int health) const = 0;
  virtual ~Consumption() {}
  Consumption(const Consumption&) = delete;
  Consumption& operator=(const Consumption&) = delete;
};

}  // namespace healthcare
#endif  // _CONSUMPTION_H_
