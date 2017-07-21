#include "fractional_consumption.h"
#include <gtest/gtest.h>

class FractionalConsumptionTest : public ::testing::Test {
public:
  FractionalConsumptionTest()
      : health_(0)
      , life_investment_(0)
      , consumption_(0) {}

protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    consumption_ = healthcare::FractionalConsumption(30);
  }
  
  int health_;
  int life_investment_;
  healthcare::FractionalConsumption consumption_;
};

TEST_F(FractionalConsumptionTest, GetConsumption) {
  ASSERT_DOUBLE_EQ(32, consumption_.GetLifeEnjoyment(life_investment_, health_));
}
