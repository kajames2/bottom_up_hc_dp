#include "period_result_iterator.h"
#include "consumption.h"
#include "health_state.h"
#include "investment.h"
#include "period_result_factory.h"
#include "regeneration.h"

#include <cmath>
#include <gtest/gtest.h>
#include <memory>
#include <algorithm>

class PeriodResultIteratorTest : public ::testing::Test {
public:
  PeriodResultIteratorTest() {}

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
    alive_state_ = healthcare::HealthState(1, 50, 50, 10);
    std::unique_ptr<const MockRegeneration> regen =
        std::make_unique<const MockRegeneration>();
    std::unique_ptr<const MockConsumption> consumption =
        std::make_unique<const MockConsumption>();
    std::unique_ptr<healthcare::PeriodResultFactory> fact =
        std::make_unique<healthcare::PeriodResultFactory>(std::move(regen), std::move(consumption));
    end_it_ = std::make_shared<healthcaredp::PeriodResultIterator>(
        std::move(fact), alive_state_, max_remaining_cash_);
  }

  int max_remaining_cash_;
  healthcare::HealthState alive_state_;
  std::shared_ptr<healthcaredp::PeriodResultIterator> end_it_;
};

TEST_F(PeriodResultIteratorTest, CorrectNumIts) {
  healthcaredp::PeriodResultIterator it = *end_it_;
  int count = 0;
  while (it) {
    ++it;
    ++count;
  }

  int expected_count = 0;
  for (int hi = 0; hi <= alive_state_.cash; hi += 10) {
    expected_count += std::min(alive_state_.cash - hi + 1, max_remaining_cash_ + 1);
  }
  ASSERT_EQ(expected_count, count);
}
