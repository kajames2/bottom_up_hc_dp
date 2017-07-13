#include "flat_harvest.h"
#include "health_state.h"
#include <gtest/gtest.h>

class FlatHarvestTest : public ::testing::Test {
public:
  FlatHarvestTest() : state_(0, 0, 0, 0), harvest_(0, 0, 0) {}

protected:
  virtual void SetUp() {
    state_ = healthcare::HealthState(1, 60, 20, 0);
    harvest_ = healthcare::FlatHarvest(1, 5, 85);
  }

  healthcare::HealthState state_;
  healthcare::FlatHarvest harvest_;
};

TEST_F(FlatHarvestTest, GetHarvest) {
  ASSERT_DOUBLE_EQ(85, harvest_.GetHarvest(state_));
  state_.period = 10;
  ASSERT_DOUBLE_EQ(0, harvest_.GetHarvest(state_));
}

TEST_F(FlatHarvestTest, InRange) {
  ASSERT_TRUE(harvest_.InRange(1));
  ASSERT_TRUE(harvest_.InRange(5));
  ASSERT_TRUE(harvest_.InRange(3));
  ASSERT_FALSE(harvest_.InRange(7));
  ASSERT_FALSE(harvest_.InRange(-1));
}
