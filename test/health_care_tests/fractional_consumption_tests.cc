#include "fractional_consumption.h"
#include <gtest/gtest.h>

#include <memory>

class FractionalConsumptionTest : public ::testing::Test {
public:
  FractionalConsumptionTest()
      : health_(0)
      , life_investment_(0)
      , consumption_() {}

protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    consumption_ = std::make_unique<healthcare::FractionalConsumption>(30);
  }
  
  int health_;
  int life_investment_;
  std::unique_ptr<healthcare::FractionalConsumption> consumption_;
};

TEST_F(FractionalConsumptionTest, GetConsumption) {
  ASSERT_DOUBLE_EQ(32, consumption_->GetLifeEnjoyment(health_, life_investment_));
}
