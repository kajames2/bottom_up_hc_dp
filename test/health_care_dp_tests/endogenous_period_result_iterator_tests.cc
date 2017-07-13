#include "endogenous_period_result_iterator.h"
#include "consumption.h"
#include "health_state.h"
#include "investment.h"
#include "period_result_factory.h"
#include "regeneration.h"

#include <cmath>
#include <gtest/gtest.h>
#include <memory>
#include <algorithm>

class EndogenousPeriodResultIteratorTest : public ::testing::Test {
public:
  EndogenousPeriodResultIteratorTest() {}

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
      return std::floor(hi / 10.);
    }
  };

  virtual void SetUp() {
    max_remaining_cash_ = 15;
    alive_state_ = std::make_shared<healthcare::HealthState>(1, 50, 50, 10);
    std::shared_ptr<const MockRegeneration> regen =
        std::make_shared<const MockRegeneration>();
    std::shared_ptr<const MockConsumption> consumption =
        std::make_shared<const MockConsumption>();
    std::shared_ptr<healthcare::PeriodResultFactory> fact =
        std::make_shared<healthcare::PeriodResultFactory>(regen, consumption);
    end_it_ = std::make_unique<healthcaredp::EndogenousPeriodResultIterator>(
        fact, alive_state_, max_remaining_cash_);
  }

  int max_remaining_cash_;
  std::shared_ptr<healthcare::HealthState> alive_state_;
  std::unique_ptr<healthcaredp::EndogenousPeriodResultIterator> end_it_;
};

TEST_F(EndogenousPeriodResultIteratorTest, CorrectNumIts) {
  healthcaredp::EndogenousPeriodResultIterator it = *end_it_;
  int count = 0;
  while (it) {
    ++it;
    ++count;
  }

  int expected_count = 0;
  for (int hi = 0; hi <= alive_state_->cash; hi += 10) {
    expected_count += std::min(alive_state_->cash - hi + 1, max_remaining_cash_ + 1);
  }
  ASSERT_EQ(expected_count, count);
}
