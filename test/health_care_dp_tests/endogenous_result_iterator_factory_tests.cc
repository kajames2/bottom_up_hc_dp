#include "endogenous_result_iterator_factory.h"
#include "consumption.h"
#include "endogenous_result_iterator.h"
#include "exogenous_health_state.h"
#include "health_state.h"
#include "investment.h"
#include "period_result_factory.h"
#include "regeneration.h"
#include "result_to_endogenous_adapter_factory.h"

#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>
#include <memory>

class PeriodResultIteratorFactoryTest : public ::testing::Test {
public:
  PeriodResultIteratorFactoryTest() {}

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
    state_ = healthcare::HealthState(1, 50, 50, 10);
    healthcaredp::ExogenousHealthState exog_state(state_);
    std::shared_ptr<const MockRegeneration> regen =
        std::make_shared<const MockRegeneration>();
    std::shared_ptr<const MockConsumption> consumption =
        std::make_shared<const MockConsumption>();
    healthcare::PeriodResultFactory fact =
        healthcare::PeriodResultFactory(regen, consumption);
    healthcaredp::ResultToEndogenousAdapterFactory end_factory(fact);
    end_it_factory_ =
        std::make_unique<healthcaredp::EndogenousResultIteratorFactory>(
            end_factory, max_remaining_cash_);
    end_it_factory_short_ =
        std::make_unique<healthcaredp::EndogenousResultIteratorFactory>(
            regen, consumption, max_remaining_cash_);
  }

  int max_remaining_cash_;
  healthcare::HealthState state_;
  std::unique_ptr<healthcaredp::EndogenousResultIteratorFactory>
      end_it_factory_;
  std::unique_ptr<healthcaredp::EndogenousResultIteratorFactory>
      end_it_factory_short_;
};

TEST_F(PeriodResultIteratorFactoryTest, CorrectNumIts) {
  healthcaredp::EndogenousResultIterator it = end_it_factory_->GetEndogenousIterator(state_);
  healthcaredp::EndogenousResultIterator it_short = end_it_factory_short_->GetEndogenousIterator(state_);
  
  int count = 0;
  //  ASSERT_EQ((*it)->GetState(), (*it_short)->GetState());
  while (it && it_short) {
    ++it;
    ++it_short;
    ++count;
  }

  int expected_count = 0;
  for (int hi = 0; hi <= state_.cash; hi += 10) {
    expected_count += std::min(state_.cash - hi + 1, max_remaining_cash_ + 1);
  }
  ASSERT_EQ(false, it || it_short);
  ASSERT_EQ(expected_count, count);
}
