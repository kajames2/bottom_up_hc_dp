#include "composite_harvest.h"
#include "linear_harvest.h"
#include "retirement_harvest.h"
#include "health_state.h"
#include <gtest/gtest.h>

#include <vector>
#include <memory>

class CompositeHarvestTest : public ::testing::Test {
public:
  CompositeHarvestTest()
      : state_(0,0,0,0)
      , harvest1_(0,0,0)
      , harvest2_(0,0)
      , harvest_() {}

protected:
  virtual void SetUp() {
    state_ = healthcare::HealthState(1, 60, 20, 140);
    harvest1_ = healthcare::LinearHarvest(1, 5, 1);
    harvest2_ = healthcare::RetirementHarvest(8, 0.5);
    harvest_.AddHarvest(std::make_shared<healthcare::LinearHarvest>(harvest1_));
    harvest_.AddHarvest(std::make_shared<healthcare::RetirementHarvest>(harvest2_));
  }

  healthcare::HealthState state_;
  healthcare::LinearHarvest harvest1_;
  healthcare::RetirementHarvest harvest2_;
  healthcare::CompositeHarvest harvest_;
};

TEST_F(CompositeHarvestTest, GetHarvest) {
  ASSERT_EQ(60, harvest_.GetHarvest(state_));
  state_.period = 7;
  ASSERT_EQ(0, harvest_.GetHarvest(state_));
  state_.period = 10;
  ASSERT_EQ(10, harvest_.GetHarvest(state_));
}

TEST_F(CompositeHarvestTest, GetWorkingHarvest) {
  ASSERT_EQ(60, harvest_.GetWorkingHarvest(state_));
  state_.period = 7;
  ASSERT_EQ(0, harvest_.GetWorkingHarvest(state_));
  state_.period = 10;
  ASSERT_EQ(0, harvest_.GetWorkingHarvest(state_));
}


TEST_F(CompositeHarvestTest, InRange) {
  ASSERT_TRUE(harvest_.InRange(1));
  ASSERT_FALSE(harvest_.InRange(7));
  ASSERT_TRUE(harvest_.InRange(8));
}
