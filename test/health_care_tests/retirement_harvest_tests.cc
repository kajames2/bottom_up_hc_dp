#include "retirement_harvest.h"
#include "health_state.h"
#include <gtest/gtest.h>

class RetirementHarvestTest : public ::testing::Test {
public:
  RetirementHarvestTest()
      : state_(0,0,0,0)
      , harvest_() {}

protected:
  virtual void SetUp() {
    state_ = healthcare::HealthState(1, 60, 20, 140);
    harvest_ = std::make_unique<healthcare::RetirementHarvest>(8, 0.6);
  }

  healthcare::HealthState state_;
  std::unique_ptr<healthcare::RetirementHarvest> harvest_;
};

TEST_F(RetirementHarvestTest, GetHarvest) {
  ASSERT_EQ(0, harvest_->GetHarvest(state_));
  state_.period = 10;
  ASSERT_EQ(12, harvest_->GetHarvest(state_));
}

TEST_F(RetirementHarvestTest, GetWorkingHarvest) {
  ASSERT_EQ(0, harvest_->GetWorkingHarvest(state_));
  state_.period = 10;
  ASSERT_EQ(0, harvest_->GetWorkingHarvest(state_));
}

TEST_F(RetirementHarvestTest, InRange) {
  ASSERT_FALSE(harvest_->InRange(1));
  ASSERT_TRUE(harvest_->InRange(8));
}
