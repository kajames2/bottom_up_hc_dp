#include "health_state.h"
#include <gtest/gtest.h>

class HealthStateTest : public ::testing::Test {
public:
  HealthStateTest()
      : alive_state_(0, 0, 0, 0), dead_state_(0, 0, 0, 0),
        dead_state_2_(0, 0, 0, 0) {}

protected:
  virtual void SetUp() {
    dead_state_2_ = healthcare::HealthState(5, -10, 0, 0);
    dead_state_ = healthcare::HealthState(2, 0, 0, 0);
    alive_state_ = healthcare::HealthState(1, 100, 20, 0);
  }

  healthcare::HealthState alive_state_;
  healthcare::HealthState dead_state_;
  healthcare::HealthState dead_state_2_;
};

TEST_F(HealthStateTest, IsAlive) {
  ASSERT_EQ(false, healthcare::IsAlive(dead_state_));
  ASSERT_EQ(false, healthcare::IsAlive(dead_state_));
  ASSERT_EQ(true, healthcare::IsAlive(alive_state_));
}
