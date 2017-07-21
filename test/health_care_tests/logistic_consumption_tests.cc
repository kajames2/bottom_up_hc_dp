#include "logistic_consumption.h"
#include <gtest/gtest.h>

class LogisticConsumptionTest : public ::testing::Test {
public:
  LogisticConsumptionTest()
      : health_(0)
      , life_investment_(0)
      , consumption_(0) {}

protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    consumption_ = healthcare::LogisticConsumption(0.05);
  }
  
  int health_;
  int life_investment_;
  healthcare::LogisticConsumption consumption_;
};

TEST_F(LogisticConsumptionTest, GetConsumption) {
  ASSERT_DOUBLE_EQ(58.48468629040039, consumption_.GetLifeEnjoyment(life_investment_, health_));
}