#include "logistic_regeneration.h"
#include <gtest/gtest.h>

class LogisticRegenerationTest : public ::testing::Test {
public:
  LogisticRegenerationTest()
      : health_(0)
      , health_investment_(0)
      , regen_(0, 0, 0) {}

protected:
  virtual void SetUp() {
    health_ = 80;
    health_investment_ = 20;
    regen_ = healthcare::LogisticRegeneration(100, 0.05, 2);
  }
  
  int health_;
  int health_investment_;
  healthcare::LogisticRegeneration regen_;
};

TEST_F(LogisticRegenerationTest, GetRegeneration) {
  ASSERT_DOUBLE_EQ(60, regen_.GetHealthRegained(health_investment_, health_));
}
