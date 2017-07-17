#include "period_result_factory.h"
#include "consumption.h"
#include "health_state.h"
#include "investment.h"
#include "regeneration.h"

#include <gtest/gtest.h>
#include <memory>

class PeriodResultFactoryTest : public ::testing::Test {
public:
  PeriodResultFactoryTest() {}

protected:
  class MockConsumption : public healthcare::Consumption {
  public:
    MockConsumption() {}
    virtual double GetLifeEnjoyment(int li, int health) const override {
      return 2 * li + health;
    }
  };

  class MockRegeneration : public healthcare::Regeneration {
  public:
    MockRegeneration() {}
    virtual int GetHealthRegained(int hi, int health) const override {
      return hi;
    }
  };

  virtual void SetUp() {
    dead_state_ = healthcare::HealthState(2, 0, 50, 20);
    alive_state_ = healthcare::HealthState(1, 50, 45, 10);
    investment_ = healthcare::Investment(20, 10);
    over_investment_ = healthcare::Investment(80, 20);
    std::shared_ptr<const MockRegeneration> regen = std::make_shared<const MockRegeneration>();
    std::shared_ptr<const MockConsumption> consumption = std::make_shared<const MockConsumption>();
    fact_ =
        std::make_unique<healthcare::PeriodResultFactory>(regen, consumption);
  }
  healthcare::HealthState dead_state_;
  healthcare::HealthState alive_state_;
  healthcare::Investment investment_;
  healthcare::Investment over_investment_;
  std::unique_ptr<healthcare::PeriodResultFactory> fact_;
};

TEST_F(PeriodResultFactoryTest, GetHealthRegained) {
  ASSERT_EQ(20, fact_->GetHealthRegained(alive_state_, investment_));
  ASSERT_EQ(0, fact_->GetHealthRegained(dead_state_, investment_));
  ASSERT_EQ(50, fact_->GetHealthRegained(alive_state_, over_investment_));
}

TEST_F(PeriodResultFactoryTest, EndAliveState) {
  healthcare::HealthState end_alive_state =
      fact_->GetPostInvestmentState(alive_state_, investment_);
  ASSERT_EQ(2, end_alive_state.period);
  ASSERT_EQ(70, end_alive_state.health);
  ASSERT_EQ(15, end_alive_state.cash);
  ASSERT_EQ(10, end_alive_state.total_working_harvest);
}

TEST_F(PeriodResultFactoryTest, EndDeadState) {
  healthcare::HealthState end_dead_state =
      fact_->GetPostInvestmentState(dead_state_, investment_);
  ASSERT_EQ(3, end_dead_state.period);
  ASSERT_EQ(0, end_dead_state.health);
  ASSERT_EQ(0, end_dead_state.cash);
  ASSERT_EQ(20, end_dead_state.total_working_harvest);
}

TEST_F(PeriodResultFactoryTest, EndOverState) {
  healthcare::HealthState end_over_state =
      fact_->GetPostInvestmentState(alive_state_, over_investment_);
  ASSERT_EQ(2, end_over_state.period);
  ASSERT_EQ(100, end_over_state.health);
  ASSERT_EQ(-55, end_over_state.cash);
  ASSERT_EQ(10, end_over_state.total_working_harvest);
}

TEST_F(PeriodResultFactoryTest, PeriodResult) {
  healthcare::HealthState end_alive_state =
      fact_->GetPostInvestmentState(alive_state_, investment_);
  healthcare::PeriodResult period_result =
      fact_->GetPeriodResult(alive_state_, investment_);
  ASSERT_EQ(end_alive_state, period_result.state);
  ASSERT_EQ(investment_, period_result.investment);
  ASSERT_EQ(fact_->GetLifeEnjoyment(alive_state_, investment_),
            period_result.enjoyment);
}

TEST_F(PeriodResultFactoryTest, GetLifeEnjoyment) {
  ASSERT_EQ(90, fact_->GetLifeEnjoyment(alive_state_, investment_));
  ASSERT_EQ(0, fact_->GetLifeEnjoyment(dead_state_, investment_));
  ASSERT_EQ(140, fact_->GetLifeEnjoyment(alive_state_, over_investment_));
}
