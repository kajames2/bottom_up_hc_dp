#include "increasing_decay_consumption.h"
#include <gtest/gtest.h>

class IncreasingDecayConsumptionTest : public ::testing::Test {
public:
  IncreasingDecayConsumptionTest()
      : health_(0)
      , life_investment_(0)
      , consumption_(0, 0, 0) {}

protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    consumption_ = healthcare::IncreasingDecayConsumption(0.05, 50, 0.3);
  }
  
  int health_;
  int life_investment_;
  healthcare::IncreasingDecayConsumption consumption_;
};

TEST_F(IncreasingDecayConsumptionTest, GetConsumption) {
  ASSERT_DOUBLE_EQ(29.70966626494221, consumption_.GetLifeEnjoyment(life_investment_, health_));
}
