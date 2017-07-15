#include "health_investment_state_factory.h"
#include "degeneration.h"
#include "harvest.h"
#include "health_state.h"

#include <gtest/gtest.h>
#include <memory>

class MockDegeneration : public healthcare::Degeneration {
public:
  MockDegeneration() {}
  virtual int GetDegeneration(int period) const override { return 5 * period; }
};

class MockHarvest : public healthcare::Harvest {
public:
  MockHarvest() {}
  virtual int
  CalculateHarvest(const healthcare::HealthState &state) const override {
    return state.period * 40;
  }
  virtual bool InRange(int period) const override { return true; }
};

class HealthInvestmentStateFactoryTest : public ::testing::Test {
public:
  HealthInvestmentStateFactoryTest() {}

protected:
  virtual void SetUp() {
    dead_state_ = healthcare::HealthState(2, 0, 50, 20);
    alive_state_ = healthcare::HealthState(1, 50, 45, 10);
    will_die_state_ = healthcare::HealthState(10, 40, 20, 50);
    std::unique_ptr<const MockHarvest> harvest =
        std::make_unique<const MockHarvest>();
    std::unique_ptr<const MockDegeneration> degen =
        std::make_unique<const MockDegeneration>();
    fact_ = std::make_unique<healthcare::HealthInvestmentStateFactory>(
        std::move(harvest), std::move(degen));
  }
  healthcare::HealthState dead_state_;
  healthcare::HealthState alive_state_;
  healthcare::HealthState will_die_state_;
  std::unique_ptr<healthcare::HealthInvestmentStateFactory> fact_;
};

TEST_F(HealthInvestmentStateFactoryTest, GetDegeneration) {
  ASSERT_EQ(0, fact_->GetDegeneration(dead_state_));
  ASSERT_EQ(5, fact_->GetDegeneration(alive_state_));
  ASSERT_EQ(40, fact_->GetDegeneration(will_die_state_));
}

TEST_F(HealthInvestmentStateFactoryTest, InvestmentAliveState) {
  healthcare::HealthState end_alive_state =
      fact_->GetInvestmentState(alive_state_);
  ASSERT_EQ(1, end_alive_state.period);
  ASSERT_EQ(45, end_alive_state.health);
  ASSERT_EQ(85, end_alive_state.cash);
  ASSERT_EQ(50, end_alive_state.total_working_harvest);
}

TEST_F(HealthInvestmentStateFactoryTest, InvestmentDeadState) {
  healthcare::HealthState end_dead_state =
      fact_->GetInvestmentState(dead_state_);
  ASSERT_EQ(2, end_dead_state.period);
  ASSERT_EQ(0, end_dead_state.health);
  ASSERT_EQ(0, end_dead_state.cash);
  ASSERT_EQ(20, end_dead_state.total_working_harvest);
}

TEST_F(HealthInvestmentStateFactoryTest, InvestmentWillDieState) {
  healthcare::HealthState end_will_die_state =
      fact_->GetInvestmentState(will_die_state_);
  ASSERT_EQ(10, end_will_die_state.period);
  ASSERT_EQ(0, end_will_die_state.health);
  ASSERT_EQ(0, end_will_die_state.cash);
  ASSERT_EQ(450, end_will_die_state.total_working_harvest);
}

TEST_F(HealthInvestmentStateFactoryTest, GetHarvest) {
  ASSERT_EQ(40, fact_->GetHarvest(alive_state_));
  ASSERT_EQ(0, fact_->GetHarvest(dead_state_));
  ASSERT_EQ(400, fact_->GetHarvest(will_die_state_));
}

TEST_F(HealthInvestmentStateFactoryTest, GetWorkingHarvest) {
  ASSERT_EQ(40, fact_->GetWorkingHarvest(alive_state_));
  ASSERT_EQ(0, fact_->GetWorkingHarvest(dead_state_));
  ASSERT_EQ(400, fact_->GetWorkingHarvest(will_die_state_));
}
