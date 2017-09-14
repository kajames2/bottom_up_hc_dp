#ifndef _CACHED_CONSUMPTION_H_
#define _CACHED_CONSUMPTION_H_

#include "consumption.h"

#include <array>
#include <vector>

namespace healthcare {
class CachedConsumption : public Consumption {
public:
  CachedConsumption() : CachedConsumption(300) {}
  CachedConsumption(int max_investment) : cache_(max_investment + 1){};

  virtual double GetLifeEnjoyment(int health, int life_investment) const override {
    return cache_[life_investment][health];
  };

protected:
  void FillCache() {
    for (int li = 0; li < cache_.size(); ++li) {
      for (int h = 0; h <= 100; ++h) {
        cache_[li][h] = this->CalculateLifeEnjoyment(h, li);
      }
    }
  }

private:
  virtual double CalculateLifeEnjoyment(int health, int life_investment) const = 0;
  std::vector<std::array<double, 101>> cache_;
};

} // namespace healthcare
#endif
