#include "shifted_logistic_regeneration.h"
#include <gtest/gtest.h>

class ShiftedLogisticRegenerationTest : public ::testing::Test {
public:
  ShiftedLogisticRegenerationTest()
      : health_(0)
      , health_investment_(0)
      , regen_(0) {}

protected:
  virtual void SetUp() {
    health_ = 80;
    health_investment_ = 20;
    regen_ = healthcare::ShiftedLogisticRegeneration(0.02);
  }
  
  int health_;
  int health_investment_;
  healthcare::ShiftedLogisticRegeneration regen_;
};

TEST_F(ShiftedLogisticRegenerationTest, GetRegeneration) {
  ASSERT_DOUBLE_EQ(5, regen_.GetHealthRegained(health_investment_, health_));
}
